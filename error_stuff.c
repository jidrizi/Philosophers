/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:26:41 by jidrizi           #+#    #+#             */
/*   Updated: 2024/11/17 17:43:46 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_msg(char *msg)
{
	write(STDERR_FILENO, "Error: ", 7);
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