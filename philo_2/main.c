/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 23:12:36 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 23:44:26 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (args_fail(WRONG_ARGC));
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) <= 0)
			return (args_fail(WRONG_INTS));
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (args_fail(WRONG_INTS));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

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
	while (check_if_running(data))
	{
		philo_eat(data, philo);
		philo_sleep(data, philo);
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
		printf("about to wait for: %i\n", i + 1);
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

	if (check_input(argc, argv))
		return (EXIT_FAILURE);
	if (init_data(&data, argv))
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
	return (0);
}
