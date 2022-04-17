/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 23:16:23 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 22:30:29 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	checks for right input format, mallocs all pointers inside data struct,
 *	initializes starting data.
 *	returns: on error EXIT_FAILURE, otherwise EXIT_SUCCESS.
 */
int	init_data(t_data **data, char **argv)
{
	*data = (t_data *)ft_calloc(1, sizeof(**data));
	if (*data == NULL)
		return (EXIT_FAILURE);
	(*data)->philo_count = ft_atoi(argv[1]);
	(*data)->die_time = ft_atoi(argv[2]);
	(*data)->eat_time = ft_atoi(argv[3]);
	(*data)->sleep_time = ft_atoi(argv[4]);
	(*data)->min_eat_count = 0;
	if (argv[5])
		(*data)->min_eat_count = ft_atoi(argv[5]);
	(*data)->thread_ids = ft_calloc((*data)->philo_count, sizeof(pthread_t));
	(*data)->forks = ft_calloc((*data)->philo_count, sizeof(pthread_mutex_t));
	(*data)->eat_time_locks = ft_calloc((*data)->philo_count,
			sizeof(pthread_mutex_t));
	(*data)->eat_count_locks = ft_calloc((*data)->philo_count,
			sizeof(pthread_mutex_t));
	if ((*data)->thread_ids == NULL || (*data)->forks == NULL
		|| (*data)->eat_time_locks == NULL || (*data)->eat_count_locks == NULL)
		return (EXIT_FAILURE);
	(*data)->err_code = 0;
	(*data)->wait_for_start = true;
	(*data)->running = true;
	return (EXIT_SUCCESS);
}

/*
 *	mallocs philos 2d array and each philo struct, sets forks and philo_num.
*	returns: on error EXIT_FAILURE, otherwise EXIT_SUCCESS.
 */
int	init_philos(t_data *data, t_philo ***philos)
{
	int	i;

	*philos = ft_calloc(data->philo_count, sizeof(t_philo *));
	if (*philos == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->philo_count)
	{
		(*philos)[i] = ft_calloc(1, sizeof(t_philo));
		if ((*philos)[i] == NULL)
			return (EXIT_FAILURE);
		(*philos)[i]->philo_num = i + 1;
		(*philos)[i]->fork_l = i;
		(*philos)[i]->fork_r = i + 1;
		if (i == data->philo_count - 1)
			(*philos)[i]->fork_r = 0;
		(*philos)[i]->eat_count = 0;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->ms_start_lock), NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(data->running_lock), NULL))
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_init(&(data->eat_time_locks[i]), NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_init(&(data->eat_count_locks[i]), NULL))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_threads(t_data *data, t_philo **philos)
{
	t_comb	*comb;
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		comb = ft_calloc(1, sizeof(t_comb));
		if (comb == NULL)
			return (EXIT_FAILURE);
		comb->data = data;
		comb->philo = philos[i];
		if (pthread_create(&(data->thread_ids[i]), NULL, &routine, comb))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
