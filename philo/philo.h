/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:32:31 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 03:13:25 by mmeising         ###   ########.fr       */
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
	EAT,
	SLEEP,
	THINK,
	FORK,
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
	int				fork_l;
	int				fork_r;
	long			eat_time;
	t_status		status;
}	t_philo;

typedef struct	s_comb
{
	t_data	*data;
	t_philo	*philo;
}	t_comb;

void	*routine(void *arg);
// void	reaper(t_data *data, t_philo *philo);

//		INITS

int	init_data(t_data *data, int argc, char **argv);
int	init_mutex(t_data *data);
int	init_threads(t_data *data, t_philo ***philo);
int	init_philo(t_philo **philo, t_data **data, t_comb **comb, int i);

//		PHILO ACTIONS

void	philo_eat(t_philo *philo, t_data *data);
void	philo_sleep(t_philo *philo, t_data *data);
void	philo_think(t_philo *philo, t_data *data);

//		UTILS

int		err_handle(t_data *data, t_error err);
void	print_stat(t_philo *philo, t_data *data, t_status stat);
int		ft_atoi(const char *str);

//		TIME FUNCTIONS

long	get_time(void);
long	timestamp(t_data *data);
void	ft_sleep(long time_ms);

#endif