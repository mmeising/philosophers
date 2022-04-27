/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:37:14 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 00:38:46 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data)
{
	data->watch_th = ft_calloc(data->philo_count, sizeof(pthread_t));
	data->pids = ft_calloc(data->philo_count, sizeof(pid_t));
	if (data->watch_th == NULL || data->pids == NULL)
		ft_exit(&data, NULL, MALLOC_FAIL);
	data->ate_enough = 0;
	data->running = true;
}

void	init_philos(t_data *data, t_philo ***philos)
{
	int	i;

	*philos = ft_calloc(data->philo_count, sizeof(t_philo *));
	if (*philos == NULL)
		ft_exit(&data, NULL, MALLOC_FAIL);
	i = 0;
	while (i < data->philo_count)
	{
		(*philos)[i] = ft_calloc(1, sizeof(t_philo));
		if ((*philos)[i] == NULL)
			ft_exit(&data, philos, MALLOC_FAIL);
		(*philos)[i]->philo_num = i + 1;
		(*philos)[i]->eat_count = 0;
		(*philos)[i]->eat_time = 0;
		i++;
	}
}

void	init_idents(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		philos[i]->eat_count_ident = ft_itoa(10001 + i);
		philos[i]->eat_time_ident = ft_itoa(20001 + i);
		if (philos[i]->eat_count_ident == NULL
			|| philos[i]->eat_time_ident == NULL)
			ft_exit(&data, &philos, MALLOC_FAIL);
		i++;
	}
}

void	init_locks(t_data *data, t_philo **philos)
{
	int	i;

	data->forks = prot_sem_open("forks", data->philo_count);
	data->start_lock = prot_sem_open("start_lock", 0);
	data->running_lock = prot_sem_open("running", 1);
	data->ate_enough_lock = prot_sem_open("ate_enough_lock", 1);
	if (data->forks == SEM_FAILED || data->start_lock == SEM_FAILED
		|| data->running_lock == SEM_FAILED
		|| data->ate_enough_lock == SEM_FAILED)
		ft_exit(&data, &philos, SEM_FAIL);
	i = 0;
	while (i < data->philo_count)
	{
		philos[i]->eat_count_lock = prot_sem_open(philos[i]->eat_count_ident, 1);
		philos[i]->eat_time_lock = prot_sem_open(philos[i]->eat_time_ident, 1);
		if (philos[i]->eat_count_lock == SEM_FAILED
			|| philos[i]->eat_time_lock == SEM_FAILED)
			ft_exit(&data, NULL, SEM_FAIL);
		i++;
	}
}

void	init_processes(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			philo_routine(data, philos, i);
		i++;
	}
}
