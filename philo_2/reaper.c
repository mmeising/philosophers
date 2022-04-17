/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:09:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 02:07:59 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reaper(t_data *data, t_philo **philos)
{
	int	i;
	long	time_of_death;

	i = 0;
	while (true)
	{
		if (i == data->philo_count)
			i = 0;
		pthread_mutex_lock(&(data->eat_time_locks[i]));
		if (timestamp(data) > philos[i]->eat_time + data->die_time)
		{
			pthread_mutex_unlock(&(data->eat_time_locks[i]));
			pthread_mutex_lock(&(data->running_lock));
			data->running = false;
			pthread_mutex_unlock(&(data->running_lock));
			time_of_death = timestamp(data);
			ft_sleep(1);
			printf(RED"%li %i died\n"RESET, timestamp(data), i + 1);
			// print_status(data, philos[i], DEAD);
			return ;
		}
		pthread_mutex_unlock(&(data->eat_time_locks[i]));
		i++;
	}
}
