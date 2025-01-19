/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:45:14 by jidrizi           #+#    #+#             */
/*   Updated: 2024/12/04 15:10:08 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// MACROS
# define IMMIDIATE_SUCCESS 3

// EXTERNAL LIBRARIES
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

// TYPES

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}	t_state;

typedef struct s_state_stuff
{
	size_t			philos;
	size_t			t2die;
	size_t			t2eat;
	size_t			t2sleep;
	size_t			meals;
	size_t			ded;
	size_t			error;
	size_t			total_meals;
	t_philo			*philo;
	pthread_mutex_t	*forks;	
	pthread_mutex_t	msg;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	sleeping_mutex;
	pthread_mutex_t	ded_mutex;
}	t_state_data;


// PROTOTYPES
void	error_msg(char *msg);
int		ft_strlen(char *str);
int		ft_isdigit(char *str);
int		ft_atoi(const char *str);
void	ft_bzero(void *mem, size_t count);
void	*ft_calloc(size_t count, size_t size);
void	init_state_data(t_state_data *s_data, int argc, char **argv);


#endif
