/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:31:38 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/14 20:26:49 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	copies arguments provided via argv into t_data struct.
 *	returns 1 if input is illegal, otherwise returns 0.
 */
int	init(t_data *data, int argc, char **argv)
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
	data->wait_for_start = true;
	data->thread_id = malloc(sizeof(int) * data->philo_count);
	if (data->thread_id == NULL)
		return (err_handle(data, MALLOC_FAILED));
	return (0);
}

void	*routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	// printf("data philo count: %i\n", data->philo_count);
	// printf("waiting...\n");
	// printf("waitforstart: %i\n", data->wait_for_start);
	while (data->wait_for_start == true)
	{
		// printf("waitforstart: %i\n", data->wait_for_start);
		usleep(100);
	}
	// printf("finished waiting\n");
	return (0);
}

void	init_philo(t_philo **philo, t_data **data, int i, int philo_count)
{
	(*philo)->fork_l = &(*data)->forks[i];
	if (i < philo_count - 1)
		(*philo)->fork_r = &(*data)->forks[i + 1];
	else
		(*philo)->fork_r = &(*data)->forks[0];
	(*philo)->philo_num = i + 1;
}

/*
 *	creates the threads, one for each philosopher.
 *	assigns the forks.
 *	creates the mutex for each philosopher's time.
 */
int	create_threads(int philo_count, t_data *data)
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

//	TO-DO: create mutexes too
int	create_forks(t_data *data)
{
	data->forks = malloc(sizeof(*data->forks) * data->philo_count);
	if (data->forks == NULL)
		return (err_handle(data, MALLOC_FAILED));
	memset(data->forks, 0, sizeof(*(data->forks)) * data->philo_count);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	*threads;
	int			i;

	threads = NULL;
	data = malloc(sizeof(*data));
	if (data == NULL)
		return (err_handle(data, MALLOC_FAILED));
	if (init(data, argc, argv) != 0)
		return (data->err_code);
	if (create_forks(data) != 0)
		return (data->err_code);
	if (create_threads(data->philo_count, data) != 0)
		return (data->err_code);
	data->wait_for_start = false;
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->thread_id[i], NULL) != 0)
			return (err_handle(data, FAILED_PTHREAD_JOIN));
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	// struct timeval	tv_start;
// 	struct timeval	tv;
// 	// int				i;

// 	// gettimeofday(&tv_start, NULL);
// 	// i = 0;
// 	while (1)
// 	{
// 		sleep(1);
// 		// i += 100;
// 		gettimeofday(&tv, NULL);
// 		printf("%li\n", tv.tv_sec * 1000 + tv.tv_usec / 1000);
// 		// printf("%i ms since start\tms delay:\t%li\n", i, ((tv.tv_sec - tv_start.tv_sec) * 1000 + (tv.tv_usec - tv_start.tv_usec) / 1000) - i);
// 		// printf("ms delay since start: %li in %li seconds\n", ((tv.tv_sec - tv_start.tv_sec) * 1000 + (tv.tv_usec)))
// 	}
// 	return (0);
// }