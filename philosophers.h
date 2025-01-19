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

// PROTOTYPES
void	error_msg(char *msg);
int		ft_strlen(char *str);
int		ft_isdigit(char *str);
int		ft_atoi(const char *str);
void	ft_bzero(void *mem, size_t count);
void	*ft_calloc(size_t count, size_t size);

#endif
