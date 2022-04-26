/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:22:55 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/27 00:09:10 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(t_data **data, t_philo ***philos, t_status stat, int i)
{
	// if (*data)
	// 	ft_free_data(data);
	// if (*philos)
	// 	ft_free_philos(philos);
	printf("inside ft_exit\n");
	(void)data;
	(void)philos;
	if (stat == MALLOC_FAIL)
		return (10);
	else if (stat == SEM_FAIL)
		return (11);
	else if (stat == DEAD)
	{
		sem_wait((*data)->running_lock);
		(*data)->running = false;
		sem_post((*data)->running_lock);
		sem_post((*data)->eat_time_locks[i]);
		return (DEAD);//20
	}
	else if (stat == ATE_ENOUGH)
	{
		sem_wait((*data)->running_lock);
		(*data)->running = false;
		sem_post((*data)->running_lock);
		sem_post((*data)->eat_count_locks[i]);
		return (ATE_ENOUGH);//21
	}
	else
		return (100);
}
