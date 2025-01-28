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
# include <stdbool.h>

// TYPES

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}	t_state;

typedef struct s_philo
{
	size_t					id;
	size_t					meal_c;
	size_t					meal_complete;
	t_state					state;
	size_t					start;
	size_t					last_eat;
	struct s_state_stuff	*sdata;
	pthread_t				thread;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
}					t_philo;

typedef struct s_state_stuff
{
	size_t			philo_count;
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
int		init_thread(t_state_data *sdata);
void	*check_routine(void *arg);

#endif
