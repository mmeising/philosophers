/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:08:22 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/27 01:01:48 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	checks for right input format, mallocs all pointers inside data struct,
 *	initializes input and starting data.
 */
void	init_data(t_data **data, char **argv)
{
	*data = (t_data *)ft_calloc(1, sizeof(**data));
	if (*data == NULL)
		exit(ft_exit(data, NULL, MALLOC_FAIL, 0));
	(*data)->philo_count = ft_atoi(argv[1]);
	(*data)->die_time = ft_atoi(argv[2]);
	(*data)->eat_time = ft_atoi(argv[3]);
	(*data)->sleep_time = ft_atoi(argv[4]);
	(*data)->min_eat_count = 0;
	if (argv[5])
		(*data)->min_eat_count = ft_atoi(argv[5]);
	(*data)->threads_watch = ft_calloc((*data)->philo_count, sizeof(pthread_t));
	(*data)->eat_time_locks = ft_calloc((*data)->philo_count, sizeof(sem_t *));
	(*data)->eat_count_locks = ft_calloc((*data)->philo_count, sizeof(sem_t *));
	(*data)->eat_time_idents = ft_calloc((*data)->philo_count, sizeof(char *));
	(*data)->eat_count_idents = ft_calloc((*data)->philo_count, sizeof(char *));
	(*data)->pids = ft_calloc((*data)->philo_count, sizeof(pid_t));
	if ((*data)->threads_watch == NULL || (*data)->eat_time_locks == NULL
		|| (*data)->eat_count_locks == NULL || (*data)->eat_time_idents == NULL
		|| (*data)->eat_count_idents == NULL || (*data)->pids == NULL)
		exit(ft_exit(data, NULL, MALLOC_FAIL, 0));
	(*data)->ate_enough_count = 0;
	(*data)->running = true;//needed for printf later, will only print statements if true
}

void	init_philos(t_data *data, t_philo ***philos)
{
	int	i;

	*philos = ft_calloc(data->philo_count, sizeof(t_philo *));
	if (*philos == NULL)
		exit(ft_exit(&data, philos, MALLOC_FAIL, 0));
	// printf("philos malloc done\n");
	i = 0;
	while (i < data->philo_count)
	{
		(*philos)[i] = ft_calloc(1, sizeof(t_philo));
		if ((*philos)[i] == NULL)
			exit(ft_exit(&data, philos, MALLOC_FAIL, 0));
		// printf("philo[i] malloc done\n");
		(*philos)[i]->philo_num = i + 1;
		(*philos)[i]->eat_count = 0;
		(*philos)[i]->eat_time = 0;
		(*philos)[i]->stat = ALIVE;
		i++;
	}
}

void	init_idents(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->eat_time_idents[i] = ft_itoa(10001 + i);
		data->eat_count_idents[i] = ft_itoa(20001 + i);
		// printf("idents mallocs\n");
		if (data->eat_time_idents[i] == NULL
			|| data->eat_count_idents[i] == NULL)
			exit(ft_exit(&data, NULL, MALLOC_FAIL, 0));
		// printf("idents mallocs done\n");
		i++;
	}
}

void	init_locks(t_data *data)
{
	int	i;

	data->forks = wrapped_sem_open("forks", data->philo_count);
	data->start_lock = wrapped_sem_open("start_lock", 0);
	data->running_lock = wrapped_sem_open("running", 1);
	data->ate_lock = wrapped_sem_open("ate_lock", 1);
	// sem_unlink("forks");
	// sem_unlink("start_lock");
	// sem_unlink("running");
	// sem_unlink("ate_lock");
	// data->forks = sem_open("forks", O_CREAT | O_EXCL, 0666, data->philo_count);
	// data->start_lock = sem_open("start_lock", O_CREAT | O_EXCL, 0666, 0);
	// data->running_lock = sem_open("running", O_CREAT | O_EXCL, 0666, 1);
	// data->ate_lock = sem_open("ate_lock", O_CREAT | O_EXCL, 0666, 1);
	if (data->forks == SEM_FAILED || data->start_lock == SEM_FAILED
		|| data->running_lock == SEM_FAILED || data->ate_lock == SEM_FAILED)
		exit(ft_exit(&data, NULL, SEM_FAIL, 0));
	i = 0;
	while (i < data->philo_count)
	{
		data->eat_time_locks[i] = wrapped_sem_open(data->eat_time_idents[i], 1);
		data->eat_count_locks[i] = wrapped_sem_open(data->eat_count_idents[i], 1);
		// sem_unlink(data->eat_time_idents[i]);
		// sem_unlink(data->eat_count_idents[i]);
		// data->eat_time_locks[i] = sem_open(data->eat_time_idents[i],
		// 	O_CREAT | O_EXCL, 0666, 1);
		// data->eat_count_locks[i] = sem_open(data->eat_count_idents[i],
		// 	O_CREAT | O_EXCL, 0666, 1);
		if (*(data->eat_time_locks) == SEM_FAILED
			|| *(data->eat_time_locks) == SEM_FAILED)
			exit(ft_exit(&data, NULL, SEM_FAIL, 0));
		i++;
	}
}

void	init_processes(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		printf("sending process number %i on its way\n", i);
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			philo_routine(data, philos, i);
		i++;
	}
	ft_sleep(1000);
	data->ms_start = timestamp(data);//does order of timestamp and
	// sleep(1);
	sem_post(data->start_lock);//sem_post make a difference in timing?
	// sleep(1);
	// sem_post_n(data->forks, 10);
	printf("sem_post in init_processes called\n");
}
