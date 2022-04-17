/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 01:50:52 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 04:16:00 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_alive(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&(data->philo_time_lock[i]));
		if (timestamp(data) > philo[i]->eat_time + data->die_t)
		{
			printf(YELLOW"i: %i about to die: %i also forks: %i %i\n"RESET, i, philo[i]->philo_num, philo[i]->fork_l, philo[i]->fork_r);
			print_stat(philo[i], data, DEAD);
			pthread_mutex_unlock(&(data->ms_start_lock));
			pthread_mutex_unlock(&(data->philo_time_lock[i]));
			return (false);
		}
		pthread_mutex_unlock(&(data->ms_start_lock));
		pthread_mutex_unlock(&(data->philo_time_lock[i]));
		i++;
	}
	return (true);
}

void	reaper(t_philo **philo, t_data *data)
{
	while (all_alive(philo, data) == true)
		continue ;
}
