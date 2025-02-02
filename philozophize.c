/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philozophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:38:45 by jidrizi           #+#    #+#             */
/*   Updated: 2025/02/01 18:42:22 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(t_philo *philo)
{
	if (check_death(philo->sdata))
		return (1);
	pthread_mutex_lock(&philo->sdata->sleeping_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->sdata->sleeping_mutex);
	philo_msg(philo);
	ft_usleep(philo->sdata->t2sleep, philo->sdata);
	return (0);
}

int	thinking(t_philo *philo)
{
	long	tt_think;

	if (check_death(philo->sdata))
		return (1);
	if (philo->sdata->philo_count % 2)
	{
		tt_think = (philo->sdata->t2eat * 2) - philo->sdata->t2sleep;
		if (tt_think < 0)
			tt_think = 0;
		ft_usleep(tt_think, philo->sdata);
	}
	pthread_mutex_lock(&philo->sdata->state_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->sdata->state_mutex);
	philo_msg(philo);
	return (0);
}

static int	forking(t_philo *philo)
{
	if (check_death(philo->sdata))
		return (1);
	pthread_mutex_lock(&philo->sdata->state_mutex);
	philo->state = FORKING;
	pthread_mutex_unlock(&philo->sdata->state_mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	philo_msg(philo);
	philo_msg(philo);
	return (0);
}

int	eating(t_philo *philo)
{
	if (forking(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	if (check_death(philo->sdata))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->sdata->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->sdata->state_mutex);
	pthread_mutex_lock(&philo->sdata->eating_mutex);
	philo->last_eat = get_current_time();
	philo->meal_c++;
	pthread_mutex_unlock(&philo->sdata->eating_mutex);
	philo_msg(philo);
	ft_usleep(philo->sdata->t2eat, philo->sdata);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = (t_philo *)philo;
	if (philo_data->id % 2)
		ft_usleep((philo_data->sdata->t2eat / 2), philo_data->sdata);
	while (1)
	{
		if (eating(philo_data) || checker(philo_data))
			break ;
		if (sleeping(philo_data) || checker(philo_data))
			break ;
		if (thinking(philo_data) || checker(philo_data))
			break ;
	}
	return (NULL);
}
