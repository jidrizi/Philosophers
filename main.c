/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:15:31 by jidrizi           #+#    #+#             */
/*   Updated: 2024/12/05 14:14:33 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//------------------------------------------------------------------------------
// ARGUMENTS MUST BE INPUT AS FOLLOWS:
// ./philo nbr_of_philo t2die t2eat t2sleep (nbr_of_meals)
//------------------------------------------------------------------------------
// ALSO THE WAY TO FORMAT THE OUTPUT IS AS FOLLOWS:
// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
//------------------------------------------------------------------------------
#include "philosophers.h"

static int	arguments_check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_msg("Invalid number of arguments..."), EXIT_FAILURE);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (IMMIDIATE_SUCCESS);
	while (--argc > 0)
		if (ft_isdigit(argv[argc]) == EXIT_FAILURE)
			return (error_msg("Arguments must be integers..."), EXIT_FAILURE);
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (EXIT_FAILURE);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (EXIT_FAILURE);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi(argv[2]));
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (IMMIDIATE_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

static int philosophize(t_state_data *sdata)
{
	t_philo		*philo_sdata;
	pthread_t	monitor_thread;
	size_t		threads_made;
	size_t		i;

	i = 0;
	threads_made = 0;
	philo_sdata = sdata->philo;
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, sdata))
		return (error("Something went wrong with monitoring thread...\n"),
			EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_state_data	sdata;
	const int	arg_check_return = arguments_check(argc, argv);

	if (arg_check_return == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (arg_check_return == IMMIDIATE_SUCCESS)
		return (EXIT_SUCCESS);
	init_state_data(&sdata, argc, argv);
	if (init_thread(&sdata) == EXIT_FAILURE)
		return (error_msg("Something went wrong when initializing thread..."),
			EXIT_FAILURE);
	if (philosophize(&sdata))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
