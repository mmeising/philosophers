/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:08:22 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/20 23:44:07 by mmeising         ###   ########.fr       */
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
		exit(MALLOC_FAIL);
	(*data)->philo_count = ft_atoi(argv[1]);
	(*data)->die_time = ft_atoi(argv[2]);
	(*data)->eat_time = ft_atoi(argv[3]);
	(*data)->sleep_time = ft_atoi(argv[4]);
	(*data)->min_eat_count = 0;
	if (argv[5])
		(*data)->min_eat_count = ft_atoi(argv[5]);
	(*data)->threads_watch = ft_calloc((*data)->philo_count, sizeof(pthread_t));
	(*data)->eat_time_locks = ft_calloc((*data)->philo_count, sizeof(sem_t));
	(*data)->eat_count_locks = ft_calloc((*data)->philo_count, sizeof(sem_t));
	(*data)->eat_time_idents = ft_calloc((*data)->philo_count, sizeof(char *));
	(*data)->eat_count_idents = ft_calloc((*data)->philo_count, sizeof(char *));
	if ((*data)->threads_watch == NULL || (*data)->eat_time_locks == NULL
		|| (*data)->eat_count_locks == NULL || (*data)->eat_time_idents == NULL
		|| (*data)->eat_count_idents == NULL)
		exit(MALLOC_FAIL);
	(*data)->running = true;
}

void	init_philos(t_data *data, t_philo ***philos)
{
	int	i;

	*philos = ft_calloc(data->philo_count, sizeof(t_philo *));
	if (*philos == NULL)
		exit(MALLOC_FAIL);
	i = 0;
	while (i < data->philo_count)
	{
		(*philos[i]) = ft_calloc(1, sizeof(t_philo));
		if ((*philos)[i] == NULL)
			exit(MALLOC_FAIL);
		(*philos)[i]->philo_num = i + 1;
		(*philos)[i]->eat_count = 0;
		(*philos)[i]->eat_time = 0;
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
		if (data->eat_time_idents[i] == NULL
			|| data->eat_count_idents[i] == NULL)
			exit(MALLOC_FAIL);
		i++;
	}
}

void	init_locks(t_data *data)
{
	int	i;

	data->forks = sem_open("forks", O_CREAT, NULL, data->philo_count);
	data->start_lock = sem_open("start_lock", O_CREAT, NULL, 0);
	data->running_lock = sem_open("running_lock", O_CREAT, NULL, 1);
	if (data->forks == SEM_FAILED || data->start_lock == SEM_FAILED
		|| data->running_lock == SEM_FAILED)
		exit(SEM_FAILED);
	i = 0;
	while (i < data->philo_count)
	{
		data->eat_time_locks[i] = sem_open(data->eat_time_idents[i],
			O_CREAT, NULL, 1);
		data->eat_count_locks[i] = sem_open(data->eat_count_idents[i],
			O_CREAT, NULL, 1);
		if (data->eat_time_locks == SEM_FAILED
			|| data->eat_count_locks == SEM_FAILED)
			exit(SEM_FAILED);
		i++;
	}
}

void	init_processes(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->threads_watch[i] = fork();
		if (data->threads_watch[i] == 0)
			philo_routine(data, philos, i);
		i++;
	}
}
