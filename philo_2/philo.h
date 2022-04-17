/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 22:23:30 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 22:34:51 by mmeising         ###   ########.fr       */
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
# include <limits.h>

# define BLUE "\033[38;5;36m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DEAD,
	WRONG_ARGC,
	WRONG_INTS
}	t_status;

typedef struct s_data
{
	int				philo_count;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			min_eat_count;
	pthread_t		*thread_ids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eat_time_locks;
	pthread_mutex_t	*eat_count_locks;
	long			ms_start;
	pthread_mutex_t	ms_start_lock;
	int				err_code;
	bool			wait_for_start;
	bool			running;
	pthread_mutex_t	running_lock;
}	t_data;

typedef struct s_philo
{
	long		eat_time;
	int			philo_num;
	int			fork_l;
	int			fork_r;
	int			eat_count;
}	t_philo;

typedef struct s_comb
{
	t_data	*data;
	t_philo	*philo;
}	t_comb;

void	print_all_data(t_data *data, t_philo **philos);

void	*routine(void *arg);
int		wait_for_threads(t_data *data);
void	reaper(t_data *data, t_philo **philos);
void	sweeper(t_data *data, t_philo **philos);

/*		inits				*/

int		init_data(t_data **data, char **argv);
int		init_philos(t_data *data, t_philo ***philos);
int		init_mutexes(t_data *data);
int		init_threads(t_data *data, t_philo **philos);

/*		actions				*/

void	philo_eat(t_data *data, t_philo *philo);
void	philo_sleep(t_data *data, t_philo *philo);
void	philo_think(t_data *data, t_philo *philo);

/*		utils				*/

void	*ft_calloc(int count, int size);
long	ft_atoi(const char *str);
void	print_status(t_data *data, t_philo *philo, t_status status);
int		args_fail(t_status err);

/*		time functions		*/

long	ft_get_time(void);
void	ft_sleep(long ms_time);
long	timestamp(t_data *data);

#endif