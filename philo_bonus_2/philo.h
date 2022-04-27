/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:53:42 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 00:31:23 by mmeising         ###   ########.fr       */
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

# define BLUE "\033[38;5;36m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef enum e_status
{
	DEAD,
	ATE_ENOUGH,
	WRONG_ARGC,
	WRONG_INTS,
	MALLOC_FAIL,
	SEM_FAIL,
	THREAD_FAIL,
	FORK,
	EAT,
	SLEEP,
	THINK
}	t_status;

typedef struct s_data
{
	int			philo_count;
	long		die_time;
	long		eat_time;
	long		sleep_time;
	long		min_eat;
	pthread_t	*watch_th;
	pid_t		*pids;
	sem_t		*forks;
	long		ms_start;
	bool		running;
	sem_t		*running_lock;
	int			ate_enough;
	sem_t		*ate_enough_lock;
	sem_t		*start_lock;
}	t_data;

typedef struct s_philo
{
	int			philo_num;
	int			eat_count;
	sem_t		*eat_count_lock;
	char		*eat_count_ident;
	long		eat_time;
	sem_t		*eat_time_lock;
	char		*eat_time_ident;
	pthread_t	reaper_th;
}	t_philo;

typedef struct s_comb
{
	t_data	*data;
	t_philo	**philos;
	int		i;
}	t_comb;

/*	input					*/

void	check_input(int argc, char **argv);
void	save_input(t_data **data, char **argv);

/*	inits					*/

void	init_data(t_data *data);
void	init_philos(t_data *data, t_philo ***philos);
void	init_idents(t_data *data, t_philo **philos);
void	init_locks(t_data *data, t_philo **philos);
void	init_processes(t_data *data, t_philo **philos);
void	watcher(t_data *data, t_philo **philos);
void	sweeper(t_data *data, t_philo **philos);

/*	routine					*/

void	philo_routine(t_data *data, t_philo **philos, int i);
void	philo_eat(t_data *data, t_philo *philo);
void	philo_sleep(t_data *data, t_philo *philo);
void	philo_think(t_data *data, t_philo *philo);

/*	utils					*/

void	ft_exit(t_data **data, t_philo ***philos, t_status err);

char	*ft_itoa(int n);
long	ft_atoi(const char *str);
void	*ft_calloc(int count, int size);

sem_t	*prot_sem_open(const char *name, int count);
void	uncomb(t_data **data, t_philo ***philos, int *i, void *arg);
void	print_statement(t_data *data, t_philo *philo, t_status stat);
void	ate_count_plus(t_data *data);

/*	time functions			*/

long	ft_get_time(void);
long	ft_timestamp(t_data *data);
void	ft_sleep(long ms_time);

#endif