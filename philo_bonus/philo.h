/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 22:23:30 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 19:19:06 by mmeising         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdatomic.h>

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
	ATE_ENOUGH,
	WRONG_ARGC,
	WRONG_INTS
}	t_status;

typedef enum e_err
{
	MALLOC_FAIL,
	WRONG_INPUT
}	t_err;

typedef struct s_data
{
	int				philo_count;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			min_eat_count;
	pthread_t		*threads_watch;
	sem_t			*forks;
	sem_t			**eat_time_locks;
	sem_t			**eat_count_locks;
	char			**eat_time_idents;
	char			**eat_count_idents;
	long			ms_start;
	sem_t			*start_lock;
	// bool			running;
	// sem_t			running_lock;//starts at 1, wait/post for each print
}	t_data;

typedef struct s_philo
{
	int			philo_num;
	int			eat_count;
	long		eat_time;
	t_status	stat;

}	t_philo;

typedef struct s_comb
{
	t_data	*data;
	t_philo	*philo;
}	t_comb;

void	reaper(t_data *data, t_philo **philos);
void	sweeper(t_data *data, t_philo **philos);

/*		inits				*/

void	init_data(t_data **data, char **argv);
void	init_philos(t_data *data, t_philo ***philos);
void	init_idents(t_data *data);
void	init_locks(t_data *data);
void	init_processes(t_data *data, t_philo **philos);

/*		actions				*/

void		*routine(void *arg);
bool		check_if_running(t_data *data);
t_status	philo_eat(t_data *data, t_philo *philo);
t_status	philo_sleep(t_data *data, t_philo *philo);
void		philo_think(t_data *data, t_philo *philo);

/*		utils				*/

void	*ft_calloc(int count, int size);
long	ft_atoi(const char *str);
char	*ft_itoa(int n);
void	print_status(t_data *data, t_philo *philo, t_status status);
int		args_fail(t_status err);
void	sem_post_n(sem_t *sem, int times);

/*		time functions		*/

long		ft_get_time(void);
void		ft_sleep(long ms_time);
t_status	ft_sleep_check(t_data *data, t_philo *philo, long ms_time);
long		timestamp(t_data *data);

#endif