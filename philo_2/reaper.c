/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:09:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 23:48:56 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	checks if philosopher i + 1 should be dead.
 */
int	check_philo(t_data *data, t_philo **philos, int i)
{
	long	time_of_death;

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
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(data->eat_time_locks[i]));
	return (EXIT_SUCCESS);
}

/*
 *	if i reached last philosopher, resets it to 0.
 *	if min_eat_times isn't set, returns EXIT_SUCCESS.
 *
 *	if min_eat_times is set: checks if all philos ate enough.
 *	if they have eaten enough: returns EXIT_FAILURE,
 *	if they haven't eaten enough: resets ate_enough to 0 
 *	and returns EXIT_SUCCESS.
 */
int	check_reset_counts(t_data *data, int *i, int *ate_enough)
{
	if (*i == data->philo_count)
	{
		*i = 0;
		if (*ate_enough == data->philo_count)
		{
			pthread_mutex_lock(&(data->running_lock));
			data->running = false;
			pthread_mutex_unlock(&(data->running_lock));
			printf(GREEN"%li everyone ate enough! stopping simulation\n"RESET,
				timestamp(data));
			return (EXIT_FAILURE);
		}
		*ate_enough = 0;
	}
	return (EXIT_SUCCESS);
}

/*
 *	cycles through all philosophers and checks if they should have died already.
 *
 *	if min_eat_timess is set, reaper also checks if all philosophers ate enough
 *	and returns if they did.
 */
void	reaper(t_data *data, t_philo **philos)
{
	int		i;
	int		ate_enough;

	i = 0;
	ate_enough = 0;
	while (true)
	{
		if (check_reset_counts(data, &i, &ate_enough))
			return ;
		if (check_philo(data, philos, i))
			return ;
		pthread_mutex_lock(&(data->eat_count_locks[i]));
		if (data->min_eat_count && philos[i]->eat_count >= data->min_eat_count)
			ate_enough++;
		pthread_mutex_unlock(&(data->eat_count_locks[i]));
		i++;
	}
}
