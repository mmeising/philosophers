/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:37:08 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 18:31:18 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_post_n(sem_t *sem, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_post(sem);
		i++;
	}
}

void	print_stat(t_data *data, t_philo *philo, t_status stat)
{
	// sem_wait(data->running_lock);
	// if (data->running == false)
	// {
	// 	sem_post(data->running_lock);
	// 	return ;
	// }
	if (stat == EAT)
		printf("%li %i is eating\n", timestamp(data), philo->philo_num);
	else if (stat == SLEEP)
		printf("%li %i is sleeping\n", timestamp(data), philo->philo_num);
	else if (stat == THINK)
		printf("%li %i is thinking\n", timestamp(data), philo->philo_num);
	else if (stat == FORK)
		printf("%li %i has taken a fork\n", timestamp(data), philo->philo_num);
	// sem_post(data->running_lock);
}
