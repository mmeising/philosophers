/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 23:12:36 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 02:04:28 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (true)
	{
		if (check_if_running(data) == false)
			break ;
		philo_eat(data, philo);
		if (check_if_running(data) == false)
			break ;
		philo_sleep(data, philo);
		if (check_if_running(data) == false)
			break ;
		philo_think(data, philo);
	}
	return (0);
}

int	wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->thread_ids[i], NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philos;

	if (init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (init_philos(data, &philos))
		return (EXIT_FAILURE);
	if (init_mutexes(data))
		return (EXIT_FAILURE);
	if (init_threads(data, philos))
		return (EXIT_FAILURE);
	data->ms_start = ft_get_time();
	data->wait_for_start = false;
	reaper(data, philos);
	sweeper(data, philos);
	// if (wait_for_threads(data))
	// 	return (EXIT_FAILURE);
	return (0);
	// print_all_data(data, philos);
}
