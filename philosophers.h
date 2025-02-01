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
	FORKING,
}	t_state;

typedef struct s_philo
{
	int						id;
	int						meal_c;
	int						meal_complete;
	t_state					state;
	long int				start;
	long int				last_eat;
	struct s_state_stuff	*sdata;
	pthread_t				thread;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
}					t_philo;

typedef struct s_state_stuff
{
	int				philo_count;
	long int		t2die;
	long int		t2eat;
	long int		t2sleep;
	int				meal_count;
	int				ded;
	int				error;
	int				total_meals;
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
size_t	get_current_time(void);
void	ft_bzero(void *mem, size_t count);
void	*ft_calloc(size_t count, size_t size);
void	init_state_data(t_state_data *s_data, int argc, char **argv);
int		init_thread(t_state_data *sdata);
void	*check_routine(void *arg);
int		set_death(t_state_data *sdata, int i);
void	free_and_exit(t_state_data *sdata);
int		create_threads(t_philo *philo_data, t_state_data *sdata);

#endif
