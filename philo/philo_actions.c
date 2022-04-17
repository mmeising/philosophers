/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:37:00 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 03:42:33 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	grab_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&(data->fork_lock[philo->fork_l]));
	print_stat(philo, data, FORK);
	pthread_mutex_lock(&(data->fork_lock[philo->fork_r]));
	print_stat(philo, data, FORK);
}

void	philo_eat(t_philo *philo, t_data *data)
{
	grab_forks(philo, data);
	pthread_mutex_lock(&(data->philo_time_lock[philo->philo_num]));
	philo->eat_time = timestamp(data);
	pthread_mutex_unlock(&(data->ms_start_lock));
	pthread_mutex_unlock(&(data->philo_time_lock[philo->philo_num]));
	print_stat(philo, data, EAT);
	ft_sleep(data->eat_t);
	pthread_mutex_unlock(&(data->fork_lock[philo->fork_l]));
	pthread_mutex_unlock(&(data->fork_lock[philo->fork_r]));
}

void	philo_sleep(t_philo *philo, t_data *data)
{
	print_stat(philo, data, SLEEP);
	ft_sleep(data->sleep_t);
}

void	philo_think(t_philo *philo, t_data *data)
{
	printf("%li %i is thinking\n", timestamp(data), philo->philo_num);
	pthread_mutex_unlock(&(data->ms_start_lock));
}
