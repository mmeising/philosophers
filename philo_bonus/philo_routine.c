/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:39:51 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 21:42:07 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_data *data, t_philo **philos, int i)
{
	t_philo	*philo;

	philo = philos[i];
	sem_wait(data->start_lock);
	sem_post(data->start_lock);
	data->ms_start = ft_get_time();
	if (philo->philo_num % 2 == 0)
	{
		if (philo_sleep(data, philo) == DEAD)
			exit(ft_exit(&data, &philos, DEAD));
	}
	printf("philo %i's stat: %i\n", philo->philo_num, philo->stat);
	while (philo->stat != DEAD)
	{
		// printf("philo %i about to eat\n", philo->philo_num);
		if (philo_eat(data, philo) == DEAD)
			exit(ft_exit(&data, &philos, DEAD));
		if (philo->stat == ATE_ENOUGH)
			exit(ft_exit(&data, &philos, ATE_ENOUGH));
		// printf("philo %i about to sleep\n", philo->philo_num);
		if (philo_sleep(data, philo) == DEAD)
			exit(ft_exit(&data, &philos, DEAD));
		// printf("philo %i about to think\n", philo->philo_num);
		philo_think(data, philo);
	}
	printf("philo %i ended while loop\n", philo->philo_num);
}

t_status	philo_eat(t_data *data, t_philo *philo)
{
	// printf("taking fork\n");
	sem_wait(data->forks);
	// printf("took fork\n");
	print_status(data, philo, FORK);
	sem_wait(data->forks);
	print_status(data, philo, FORK);
	print_status(data, philo, EAT);
	philo->eat_time = timestamp(data);
	if (ft_sleep_check(data, philo, data->eat_time) == DEAD)
		return (DEAD);
	philo->eat_count++;
	sem_post(data->forks);
	sem_post(data->forks);
	if (data->min_eat_count > 0 && philo->eat_count >= data->min_eat_count)
		philo->stat = ATE_ENOUGH;
	return (0);
}

t_status	philo_sleep(t_data *data, t_philo *philo)
{
	print_status(data, philo, SLEEP);
	if (ft_sleep_check(data, philo, data->sleep_time) == DEAD)
		return (DEAD);
	return (0);
}

void	philo_think(t_data *data, t_philo *philo)
{
	print_status(data, philo, THINK);
}
