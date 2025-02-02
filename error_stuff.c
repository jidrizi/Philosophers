/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:26:41 by jidrizi           #+#    #+#             */
/*   Updated: 2025/02/01 18:12:26 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

int	set_death(t_state_data *sdata, int i)
{
	long	now;

	pthread_mutex_lock(&sdata->state_mutex);
	pthread_mutex_lock(&sdata->eating_mutex);
	now = get_current_time();
	if (now - sdata->philo[i].last_eat >= sdata->t2die
		&& sdata->philo[i].state != EATING)
	{
		pthread_mutex_lock(&sdata->ded_mutex);
		sdata->ded = 1;
		pthread_mutex_unlock(&sdata->ded_mutex);
		sdata->philo[i].state = DEAD;
		pthread_mutex_unlock(&sdata->eating_mutex);
		pthread_mutex_unlock(&sdata->state_mutex);
		pthread_mutex_lock(&sdata->msg);
		printf("%ld %d died\n", get_current_time() - sdata->philo[i].start,
			sdata->philo[i].id);
		pthread_mutex_unlock(&sdata->msg);
		return (1);
	}
	pthread_mutex_unlock(&sdata->eating_mutex);
	pthread_mutex_unlock(&sdata->state_mutex);
	return (0);
}

void	free_and_exit(t_state_data *sdata)
{
	int	i;

	i = 0;
	if (sdata->philo)
	{
		while (i < sdata->philo_count)
		{
			pthread_mutex_destroy(&sdata->forks[i]);
			i++;
		}
		free(sdata->philo);
		sdata->philo = NULL;
	}
	if (sdata->forks)
	{
		free(sdata->forks);
		sdata->forks = NULL;
	}
	pthread_mutex_destroy(&sdata->state_mutex);
	pthread_mutex_destroy(&sdata->eating_mutex);
	pthread_mutex_destroy(&sdata->msg);
	pthread_mutex_destroy(&sdata->ded_mutex);
	pthread_mutex_destroy(&sdata->sleeping_mutex);
}

void	philo_msg(t_philo *philo)
{
	if (check_death(philo->sdata))
		return ;
	pthread_mutex_lock(&philo->sdata->msg);
	pthread_mutex_lock(&philo->sdata->state_mutex);
	if (philo->state == FORKING)
		printf("%ld %d has taken a fork\n", get_current_time() - philo->start,
			philo->id);
	else if (philo->state == EATING)
		printf("%ld %d is eating\n", get_current_time() - philo->start,
			philo->id);
	else if (philo->state == SLEEPING)
		printf("%ld %d is sleeping\n", get_current_time() - philo->start,
			philo->id);
	else if (philo->state == THINKING)
		printf("%ld %d is thinking\n", get_current_time() - philo->start,
			philo->id);
	pthread_mutex_unlock(&philo->sdata->msg);
	pthread_mutex_unlock(&philo->sdata->state_mutex);
}
