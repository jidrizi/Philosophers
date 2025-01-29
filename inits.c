/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 21:14:06 by jidrizi           #+#    #+#             */
/*   Updated: 2025-01-19 21:14:06 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_state_data(t_state_data *s_data, int argc, char **argv)
{
	s_data->philo_count = ft_atoi(argv[1]);
	s_data->t2die = ft_atoi(argv[2]);
	s_data->t2eat = ft_atoi(argv[3]);
	s_data->t2sleep = ft_atoi(argv[4]);
	s_data->error = 0;
	s_data->ded = 0;
	s_data->total_meals = 0;
	if (argc == 6)
		s_data->meal_count = ft_atoi(argv[5]);
	else
		s_data->meal_count = -1;
	return (0);
}

static void	init_philo(t_state_data *sdata)
{
	int	i;

	i = 0;
	while (i < sdata->philo_count)
	{
		sdata->philo[i].id = i + 1;
		sdata->philo[i].meal_c = 0;
		sdata->philo[i].meal_complete = 0;
		sdata->philo[i].state = THINKING;
		sdata->philo[i].start = get_current_time();
		sdata->philo[i].last_eat = get_current_time();
		sdata->philo[i].sdata = sdata;
		sdata->philo[i].r_fork = &sdata->forks[sdata->philo[i].id - 1];
		if (sdata->philo[i].id == sdata->philo_count)
			sdata->philo[i].l_fork = &sdata->forks[0];
		else
			sdata->philo[i].l_fork = &sdata->forks[sdata->philo[i].id];
		i++;
	}
}

static int	init_mutex(t_state_data *sdata)
{
	int	i;

	i = 0;
	while (i < sdata->philo_count)
	{
		if (pthread_mutex_init(&(sdata->forks[i]), NULL))
			return (EXIT_FAILURE);
		i++;
	}
	if (pthread_mutex_init(&sdata->msg, NULL)
	|| pthread_mutex_init(&sdata->state_mutex, NULL)
	|| pthread_mutex_init(&sdata->eating_mutex, NULL)
	|| pthread_mutex_init(&sdata->sleeping_mutex, NULL)
	|| pthread_mutex_init(&sdata->ded_mutex, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_thread(t_state_data *sdata)
{
	sdata->philo = malloc(sizeof(t_philo) * sdata->philo_count);
	if (!sdata->philo)
		return (EXIT_FAILURE);
	sdata->forks = malloc(sizeof(pthread_mutex_t) * sdata->philo_count);
	if (!sdata->forks)
		return (free(sdata->philo), EXIT_FAILURE);
	if (init_mutex(sdata) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_philo(sdata);
	return (EXIT_SUCCESS);
}
