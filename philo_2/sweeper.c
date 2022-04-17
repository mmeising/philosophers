/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sweeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:21:49 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/18 00:30:07 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&(data->ms_start_lock));
	pthread_mutex_destroy(&(data->running_lock));
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->eat_time_locks[i]));
		i++;
	}
}

void	free_philos(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		free(philos[i]);
		philos[i] = NULL;
		i++;
	}
	free(philos);
	philos = NULL;
}

void	free_data(t_data *data)
{
	free(data->thread_ids);
	data->thread_ids = NULL;
	free(data->forks);
	data->forks = NULL;
	free(data->eat_time_locks);
	data->eat_time_locks = NULL;
	free(data);
	data = NULL;
}

/*
 *	takes care of freeing all mutexes, philos and data.
 */
void	sweeper(t_data *data, t_philo **philos)
{
	ft_sleep(1000);
	destroy_mutexes(data);
	free_philos(data, philos);
	free_data(data);
}
