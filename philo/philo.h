/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:32:31 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/12 19:57:53 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum	e_error
{
	NO_ERROR,
	MALLOC_FAILED,
	TIME_NOT_POSITIVE,
	WRONG_PHILO_COUNT,
	WRONG_ARGC,
	FAILED_CREATE_FORKS,
	FAILED_CREATE_THREADS,
	FAILED_PTHREAD_JOIN,
	FAILED_INIT
}	t_error;

typedef enum	e_status
{
	IDLE,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_status;

typedef struct s_philo
{
	struct timeval	tv;
	struct timeval	tv_eat;
	struct timeval	tv_sleep;
	struct timeval	tv_think;
	t_status		stat;
}	t_philo;

typedef struct	s_data
{
	int		philo_count;
	int		die_t;
	int		eat_t;
	int		sleep_t;
	int		wait_for_start;
	t_philo	*philos;
	int		*forks;
	t_error	err_code;
}	t_data;

int	ft_atoi(const char *str);
int	err_handle(t_data *data, t_error err);

#endif