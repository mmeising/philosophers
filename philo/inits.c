/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:08:32 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/14 21:29:34 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	copies arguments provided via argv into t_data struct,
 *	sets waiting bool, malloc's pointers in data struct.
 */
int	init_data(t_data *data, int argc, char **argv)
{
	data->err_code = NO_ERROR; 
	if (argc != 5)
		return (err_handle(data, WRONG_ARGC));
	data->philo_count = ft_atoi(argv[1]);
	data->die_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sleep_t = ft_atoi(argv[4]);
	if (data->die_t <= 0 || data->eat_t <= 0 || data->sleep_t <= 0)
		return (err_handle(data, TIME_NOT_POSITIVE));
	if (data->philo_count < 1 || data->philo_count > 200)
		return (err_handle(data, WRONG_PHILO_COUNT));
	data->thread_id = malloc(sizeof(int) * data->philo_count);
	if (data->thread_id == NULL)
		return (err_handle(data, MALLOC_FAILED));
	data->forks = malloc(sizeof(*data->forks) * data->philo_count);
	if (data->forks == NULL)
		return (err_handle(data, MALLOC_FAILED));
	memset(data->forks, 0, sizeof(*(data->forks)) * data->philo_count);
	data->wait_for_start = true;
	return (0);
}

/*
 *	initializes mutex locks for forks and each philosopher's time.
 */
int	init_mutex(t_data *data)
{
	int	i;

	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->philo_time_lock = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (data->fork_lock == NULL || data->philo_time_lock == NULL)
		return (err_handle(data, MALLOC_FAILED));
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&(data->fork_lock[i]), NULL);
		pthread_mutex_init(&(data->philo_time_lock[i]), NULL);
		i++;
	}
	return (0);
}

/*
 *	creates the threads, one for each philosopher.
 */
int	init_threads(int philo_count, t_data *data)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = malloc(sizeof(*philo));
	data->forks = malloc(data->philo_count);
	if (data->forks == NULL || philo == NULL)
		return (err_handle(data, MALLOC_FAILED));
	philo->data = data;
	philo->status = IDLE;
	while (i < philo_count)
	{
		init_philo(&philo, &data, i, philo_count);
		if (pthread_create(&(data->thread_id[i]), NULL, &routine, philo))
			return (err_handle(data, FAILED_CREATE_THREADS));
		i++;
	}
	i = 0;
	return (0);
}

/*
 *	sets the fork pointers of each philosopher to the forks next to them.
 */
void	init_philo(t_philo **philo, t_data **data, int i, int philo_count)
{
	(*philo)->fork_l = &(*data)->forks[i];
	if (i < philo_count - 1)
		(*philo)->fork_r = &(*data)->forks[i + 1];
	else
		(*philo)->fork_r = &(*data)->forks[0];
	(*philo)->philo_num = i + 1;
}
