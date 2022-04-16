/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:52:23 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 01:08:19 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->forks[philo->fork_l]));
	print_status(data, philo, FORK);
	pthread_mutex_lock(&(data->forks[philo->fork_r]));
	print_status(data, philo, FORK);
	philo->eat_time = timestamp(data);
	print_status(data, philo, EAT);
	ft_sleep(data->sleep_time);
	pthread_mutex_unlock(&(data->forks[philo->fork_l]));
	pthread_mutex_unlock(&(data->forks[philo->fork_r]));
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	print_status(data, philo, SLEEP);
	ft_sleep(data->sleep_time);
}

void	philo_think(t_data *data, t_philo *philo)
{
	print_status(data, philo, THINK);
}
