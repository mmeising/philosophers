/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:32:31 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/14 20:21:11 by mmeising         ###   ########.fr       */
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
# include <stdbool.h>

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
	FAILED_INIT,
	FAILED_INIT_PHILO
}	t_error;

typedef enum	e_status
{
	IDLE,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_status;

typedef struct	s_data
{
	int			philo_count;
	int			die_t;
	int			eat_t;
	int			sleep_t;
	bool		wait_for_start;
	int			*forks;
	pthread_t	*thread_id;
	t_error		err_code;
}	t_data;

typedef struct s_philo
{
	int				philo_num;
	int				*fork_l;
	int				*fork_r;
	struct timeval	tv;
	struct timeval	tv_eat;
	struct timeval	tv_sleep;
	struct timeval	tv_think;
	t_status		status;
	t_data			*data;
}	t_philo;

int	ft_atoi(const char *str);
int	err_handle(t_data *data, t_error err);

#endif