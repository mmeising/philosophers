/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:52:23 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/18 00:25:25 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	process routine of every philosopher.
 *
 *	when everything is ready, data->wait_for_start will be set to false
 *	and the philosophers can start.
 *	every second philosopher starts by going to sleep.
 */
void	*routine(void *arg)
{
	t_comb	*comb;
	t_data	*data;
	t_philo	*philo;

	comb = (t_comb *)arg;
	data = comb->data;
	philo = comb->philo;
	free(comb);
	while (data->wait_for_start == true)
		continue ;
	if (philo->philo_num % 2 == 0)
		philo_sleep(data, philo);
	while (check_if_running(data))
	{
		philo_eat(data, philo);
		philo_sleep(data, philo);
		philo_think(data, philo);
	}
	return (0);
}

/*
 *	checks if the simulation should still be running.
 */
bool	check_if_running(t_data *data)
{
	pthread_mutex_lock(&(data->running_lock));
	if (data->running == false)
	{
		pthread_mutex_unlock(&(data->running_lock));
		return (false);
	}
	pthread_mutex_unlock(&(data->running_lock));
	return (true);
}

/*
 *	philosopher tries to grab both forks, eat and wait for eat_time.
 */
void	philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->forks[philo->fork_l]));
	print_status(data, philo, FORK);
	pthread_mutex_lock(&(data->forks[philo->fork_r]));
	print_status(data, philo, FORK);
	pthread_mutex_lock(&(data->eat_time_locks[philo->philo_num - 1]));
	philo->eat_time = timestamp(data);
	pthread_mutex_unlock(&(data->eat_time_locks[philo->philo_num - 1]));
	print_status(data, philo, EAT);
	ft_sleep(data->eat_time);
	pthread_mutex_unlock(&(data->forks[philo->fork_l]));
	pthread_mutex_unlock(&(data->forks[philo->fork_r]));
	pthread_mutex_lock(&(data->eat_count_locks[philo->philo_num - 1]));
	philo->eat_count++;
	pthread_mutex_unlock(&(data->eat_count_locks[philo->philo_num - 1]));
}

/*
 *	philosopher waits for sleep_time.
 */
void	philo_sleep(t_data *data, t_philo *philo)
{
	print_status(data, philo, SLEEP);
	ft_sleep(data->sleep_time);
}

/*
 *	only prints the think statement.
 */
void	philo_think(t_data *data, t_philo *philo)
{
	print_status(data, philo, THINK);
}
