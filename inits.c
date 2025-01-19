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
	s_data->philos = ft_atoi(argv[1]);
	s_data->t2die = ft_atoi(argv[2]);
	s_data->t2eat = ft_atoi(argv[3]);
	s_data->t2sleep = ft_atoi(argv[4]);
	s_data->error = 0;
	s_data->ded = 0;
	s_data->total_meals = 0;
	if (argc == 6)
		s_data->meals = ft_atoi(argv[5]);
	else
		s_data->meals = -1;
	return (0);
}
