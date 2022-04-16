/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:08:32 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 03:02:48 by mmeising         ###   ########.fr       */
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
int	init_threads(t_data *data, t_philo ***philo)
{
	t_comb		*comb;
	int			i;

	i = 0;
	*philo = malloc(sizeof(**philo) * data->philo_count);
	while (i < data->philo_count)
	{
		if (init_philo(*philo, &data, &comb, i) != 0)
			return (data->err_code);
		if (pthread_create(&(data->thread_id[i]), NULL, &routine, comb))
			return (err_handle(data, FAILED_CREATE_THREADS));
		i++;
	}
	return (0);
}

/*
 *	sets the fork pointers of each philosopher to the forks next to them.
 */
int	init_philo(t_philo **philo, t_data **data, t_comb **comb, int i)
{
	*comb = malloc(sizeof(**comb));
	philo[i] = malloc(sizeof(**philo));
	if (*comb == NULL || philo[i] == NULL)
		return (err_handle(*data, MALLOC_FAILED));
	(*data)->forks = malloc((*data)->philo_count);
	if ((*data)->forks == NULL || philo[i] == NULL)
		return (err_handle(*data, MALLOC_FAILED));
	philo[i]->status = IDLE;
	philo[i]->fork_l = i;
	philo[i]->fork_r = i + 1;
	if (i == (*data)->philo_count - 1)
		philo[i]->fork_r = 0;
	philo[i]->philo_num = i + 1;
	(*comb)->philo = philo[i];
	(*comb)->data = *data;
	return (0);
}
