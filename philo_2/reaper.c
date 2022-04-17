/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:09:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 22:42:27 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reaper(t_data *data, t_philo **philos)
{
	int		i;
	long	time_of_death;
	int		philos_eaten_enough;

	i = 0;
	philos_eaten_enough = 0;
	while (true)
	{
		if (i == data->philo_count)
		{
			i = 0;
			if (philos_eaten_enough == data->philo_count)
			{
				pthread_mutex_lock(&(data->running_lock));
				data->running = false;
				pthread_mutex_unlock(&(data->running_lock));
				printf(GREEN"everyone ate enough! stopping simulation\n"RESET);
				return ;
			}
			philos_eaten_enough = 0;
		}
		pthread_mutex_lock(&(data->eat_time_locks[i]));
		if (timestamp(data) > philos[i]->eat_time + data->die_time)
		{
			pthread_mutex_unlock(&(data->eat_time_locks[i]));
			pthread_mutex_lock(&(data->running_lock));
			data->running = false;
			pthread_mutex_unlock(&(data->running_lock));
			time_of_death = timestamp(data);
			ft_sleep(1);
			printf(RED"%li %i died\n"RESET, time_of_death, i + 1);
			return ;
		}
		pthread_mutex_lock(&(data->eat_count_locks[i]));
		if (data->min_eat_count && philos[i]->eat_count >= data->min_eat_count)
			philos_eaten_enough++;
		pthread_mutex_unlock(&(data->eat_count_locks[i]));
		pthread_mutex_unlock(&(data->eat_time_locks[i]));
		i++;
	}
}
