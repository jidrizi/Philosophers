/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk_what_to_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-28 20:55:07 by jidrizi           #+#    #+#             */
/*   Updated: 2025-01-28 20:55:07 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	checker(t_philo *philo)
{
	if (time_check(philo->sdata))
		return (1);
	if (meal_check(philo->sdata))
		return (1);
	if (check_death(philo->sdata))
		return (1);
	return (0);
}

static int	check_death(t_state_data *sdata)
{
	pthread_mutex_lock(&sdata->ded_mutex);
	if (sdata->ded)
	{
		pthread_mutex_unlock(&sdata->ded_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sdata->ded_mutex);
	return (0);
}

static int	time_check(t_state_data *sdata)
{
	int		i;

	i = -1;
	if (check_death(sdata))
		return (1);
	while (++i < sdata->philo_count)
	{
		if (set_death(sdata, i))
			return (1);
	}
	return (0);
}

static int	meal_check(t_state_data *sdata)
{
	int	i;

	i = 0;
	if (sdata->meal_count == -1)
		return (0);
	while (i < sdata->philo_count)
	{
		pthread_mutex_lock(&sdata->eating_mutex);
		if (sdata->philo[i].meal_c >= sdata->meal_count && \
				!sdata->philo[i].meal_complete)
		{
			sdata->total_meals++;
			sdata->philo[i].meal_complete = 1;
		}
		pthread_mutex_unlock(&sdata->eating_mutex);
		i++;
	}
	pthread_mutex_lock(&sdata->eating_mutex);
	if (sdata->total_meals == sdata->philo_count)
	{
		pthread_mutex_unlock(&sdata->eating_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sdata->eating_mutex);
	return (0);
}

void	*check_routine(void *arg)
{
	t_state_data	*sdata;
	bool			stop;

	sdata = (t_state_data *)arg;
	stop = false;
	while (stop != true)
	{
		if (time_check(sdata) || meal_check(sdata) || check_death(sdata))
			stop = true;
		usleep(500);
	}
}