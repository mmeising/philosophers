/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:08:32 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 00:19:53 by mmeising         ###   ########.fr       */
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
		// pthread_mutex_init(&(data->philo_time_lock[i]), NULL);
		i++;
	}
	return (0);
}

/*
 *	creates the threads, one for each philosopher.
 */
int	init_threads(t_data *data, t_philo **philo)
{
	t_comb		*comb;
	int			i;
	int			j = 0;

	i = 0;
	// printf("philo_count: %i, sizeof philo: %li, size *philo: %li, size **philo: %li, size ***philo: %li\n", data->philo_count, sizeof(t_philo ***), sizeof(t_philo **), sizeof(t_philo *), sizeof(t_philo));
	// return (5);
	// *philo = (t_philo **)malloc(sizeof(t_philo *) * data->philo_count * 8);
	printf(PURPLE"before init_threads:\t%p\n"RESET, philo[0]);
	while (i < data->philo_count)
	{
		if (init_philo(philo[i], data, i) != 0)
			return (data->err_code);
		while (j <= data->philo_count)
		{
			printf(PURPLE"after init_philo:\t%p\t%i\n"RESET, philo[j], j + 1);
			j++;
		}
		j = 0;
		comb = malloc(sizeof(*comb));
		if (comb == NULL)
			return (err_handle(data, MALLOC_FAILED));
		comb->philo = philo[i];
		comb->data = data;
		if (pthread_create(&(data->thread_id[i]), NULL, &routine, comb))
			return (err_handle(data, FAILED_CREATE_THREADS));
		// free(comb);
		usleep(1000);
		i++;
	}
	return (0);
}

/*
 *	sets the fork pointers of each philosopher to the forks next to them.
 */
int	init_philo(t_philo *philo, t_data *data, int i)
{
	// philo = (t_philo *)malloc(sizeof(t_philo));
	// if (philo == NULL)
	// 	return (err_handle(data, MALLOC_FAILED));
	philo->status = IDLE;
	philo->fork_l = i;
	philo->fork_r = i + 1;
	if (i == data->philo_count - 1)
		philo->fork_r = 0;
	philo->philo_num = i + 1;
	printf(RED"inside init philo i: %i, addr: %p, num: %i\n"RESET, i, philo, philo->philo_num);
	return (0);
}
