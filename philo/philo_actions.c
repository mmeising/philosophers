/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:37:00 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 03:17:26 by mmeising         ###   ########.fr       */
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
	philo->eat_time = timestamp(data);
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
}
