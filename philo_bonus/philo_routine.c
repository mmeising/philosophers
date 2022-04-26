/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:39:51 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/27 01:04:22 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//thread to regularly check if philo died or ate enough
//need to combine beginning into one "uncomb" function to save lines
void	*reaper_thread(void *arg)
{
	t_comb	*comb;
	t_data	*data;
	t_philo **philos;
	int		i;

	comb = (t_comb *)arg;
	data = comb->data;
	philos = comb->philos;
	i = comb->i;
	free(comb);
	sem_wait(data->start_lock);
	sem_post(data->start_lock);
	while (usleep(1000) == 0)
	{
		if (data->min_eat_count)
		{
			sem_wait(data->eat_count_locks[i]);
			if (philos[i]->eat_count == data->min_eat_count)
				exit(ft_exit(&data, &philos, ATE_ENOUGH, i));
			sem_post(data->eat_count_locks[i]);
		}
		sem_wait(data->eat_time_locks[i]);
		if (philos[i]->eat_time + data->die_time > timestamp(data))
			exit(ft_exit(&data, &philos, DEAD, i));
		sem_post(data->eat_time_locks[i]);
	}
	return (NULL);
}

void	philo_routine(t_data *data, t_philo **philos, int i)
{
	t_philo	*philo;
	t_comb	*comb;

	comb = ft_calloc(1, sizeof(t_comb));
	if (comb == NULL)
		exit(MALLOC_FAIL);
	comb->data = data;
	comb->philos = philos;
	comb->i = i;
	pthread_create(&(philos[i]->reaper_thread), NULL, reaper_thread, comb);
	philo = philos[i];
	sem_wait(data->start_lock);
	sem_post(data->start_lock);
	data->ms_start = ft_get_time();
	if (philo->philo_num % 2 == 0)
		philo_sleep(data, philo);
	while (true/*philo->stat != DEAD*/)
	{
		philo_eat(data, philo);
		philo_sleep(data, philo);
		philo_think(data, philo);
	}
	// printf("philo %i ended while loop\n", philo->philo_num);
}

void	philo_eat(t_data *data, t_philo *philo)
{
	// printf("taking fork philo %i\n", philo->philo_num);
	sem_wait(data->forks);
	// printf("took fork\n");
	print_status(data, philo, FORK);
	sem_wait(data->forks);
	print_status(data, philo, FORK);
	print_status(data, philo, EAT);
	sem_wait(data->eat_time_locks[philo->philo_num - 1]);
	philo->eat_time = timestamp(data);
	sem_post(data->eat_time_locks[philo->philo_num - 1]);
	ft_sleep(data->eat_time);
	sem_wait(data->eat_count_locks[philo->philo_num - 1]);
	philo->eat_count++;
	sem_post(data->eat_count_locks[philo->philo_num - 1]);
	sem_post(data->forks);
	sem_post(data->forks);
	// printf("%li philo number %i put 2 forks down\n", timestamp(data), philo->philo_num);
	if (data->min_eat_count > 0 && philo->eat_count >= data->min_eat_count)
		philo->stat = ATE_ENOUGH;
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
