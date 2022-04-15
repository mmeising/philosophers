/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:32:31 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 01:00:06 by mmeising         ###   ########.fr       */
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
	int				philo_count;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	bool			wait_for_start;
	int				*forks;
	pthread_t		*thread_id;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	*philo_time_lock;
	long			ms_start;
	t_error		err_code;
}	t_data;

typedef struct s_philo
{
	int				philo_num;
	int				*fork_l;//pointer because they onlypoint to
	int				*fork_r;//the real fork from the array in data
	long			timestamp;
	long			eat_time;
	struct timeval	tv_sleep;
	struct timeval	tv_think;
	t_status		status;
	t_data			*data;
}	t_philo;

typedef struct	s_comb
{
	t_data	*data;
	t_philo	*philo;
}	t_comb;

void	*routine(void *arg);

//		INITS

int	init_data(t_data *data, int argc, char **argv);
int	init_mutex(t_data *data);
int	init_threads(int philo_count, t_data *data);
int	init_philo(t_philo **philo, t_data **data, int i, int philo_count);

//		PHILO ACTIONS

// void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
// void	philo_think(t_philo *philo);

//		UTILS

int	ft_atoi(const char *str);
int	err_handle(t_data *data, t_error err);

//		TIME FUNCTIONS

long	get_time(void);
long	timestamp(t_philo *philo);
void	ft_sleep(long time_ms);

#endif