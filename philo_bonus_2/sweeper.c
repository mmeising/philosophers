/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sweeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:14:34 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 01:07:04 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_close_all(t_data *data, t_philo **philos)
{
	int	i;

	sem_close(data->forks);
	sem_close(data->start_lock);
	sem_close(data->running_lock);
	sem_close(data->ate_enough_lock);
	i = 0;
	while (i < data->philo_count)
	{
		sem_close(philos[i]->eat_count_lock);
		sem_close(philos[i]->eat_time_lock);
		i++;
	}
}

void	sweeper(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->watch_th[i], NULL) != 0)
			ft_exit(&data, &philos, THREAD_FAIL);
		// printf("waited for philo %i\n", philos[i]->philo_num);
		i++;
	}
	if (data->min_eat && data->ate_enough == data->philo_count)
		printf(GREEN"everyone ate enough\n"RESET);
	sem_close_all(data, philos);
}
