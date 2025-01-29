/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 21:51:32 by jidrizi           #+#    #+#             */
/*   Updated: 2025-01-28 21:51:32 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	create_threads(t_philo *philo_data, t_state_data *sdata)
{
	int	i;
	int	stop;
	int	threads_made;

	i = 0;
	threads_made = 0;
	while (++i < sdata->philo_count)
	{
		philo_data = &sdata->philo[i];
		pthread_mutex_lock(&sdata->ded_mutex);
		stop = sdata->ded;
		pthread_mutex_unlock(&sdata->ded_mutex);
		if (stop)
			break ;
		if (pthread_create(&philo_data->thread, NULL, &philo, philo_data))
		{
			error_msg("Something went wrong with create threads...\n");
			break ;
		}
		threads_made++;
		i++;
	}
	return (threads_made);
}
