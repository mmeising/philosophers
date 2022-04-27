/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 22:05:30 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 01:04:55 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper_thread(void *arg)
{
	t_data	*data;
	t_philo	**philos;
	int		i;

	uncomb(&data, &philos, &i, arg);
	sem_wait(data->start_lock);
	// data->ms_start = ft_get_time();
	sem_post(data->start_lock);
	while (data->ms_start == 0)
		continue ;
	while (true)
	{
		if (data->min_eat)
		{
			sem_wait(philos[i]->eat_count_lock);
			if (philos[i]->eat_count >= data->min_eat)
				ft_exit(&data, &philos, ATE_ENOUGH);
			sem_post(philos[i]->eat_count_lock);
		}
		sem_wait(philos[i]->eat_time_lock);
		if (philos[i]->eat_time + data->die_time < ft_timestamp(data))
			ft_exit(&data, &philos, DEAD);
		sem_post(philos[i]->eat_time_lock);
		usleep(500);
	}
}

void	philo_routine(t_data *data, t_philo **philos, int i)
{
	t_comb	*comb;

	comb = ft_calloc(1, sizeof(t_comb));
	if (comb == NULL)
		ft_exit(&data, &philos, MALLOC_FAIL);
	comb->data = data;
	comb->philos = philos;
	comb->i = i;
	pthread_create(&(philos[i]->reaper_th), NULL, reaper_thread, comb);
	sem_wait(data->start_lock);
	data->ms_start = ft_get_time();
	sem_post(data->start_lock);
	if (philos[i]->philo_num % 2 == 0)//maybe i don't need this sleep in bonus
		philo_sleep(data, philos[i]);
	while (true)
	{
		philo_eat(data, philos[i]);
		philo_sleep(data, philos[i]);
		philo_think(data, philos[i]);
	}
}

void	philo_eat(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	print_statement(data, philo, FORK);
	sem_wait(data->forks);
	print_statement(data, philo, FORK);
	sem_wait(philo->eat_time_lock);
	print_statement(data, philo, EAT);
	philo->eat_time = ft_timestamp(data);
	sem_post(philo->eat_time_lock);
	ft_sleep(data->eat_time);
	sem_post(data->forks);
	sem_post(data->forks);
	sem_wait(philo->eat_count_lock);
	philo->eat_count++;
	sem_post(philo->eat_count_lock);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	print_statement(data, philo, SLEEP);
	ft_sleep(data->sleep_time);
}

void	philo_think(t_data *data, t_philo *philo)
{
	print_statement(data, philo, THINK);
}
