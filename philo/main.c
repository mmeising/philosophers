/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:31:38 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/11 21:08:41 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	copies arguments provided via argv into t_data struct.
 *	returns 1 if input is illegal, otherwise returns 0.
 */
int	init(t_data *data, int argc, char **argv)
{
	if (argc != 5)
	{
		printf("usage (time in ms): ./philo num_of_philo time_to_die ");
		printf("time_to_eat time_to_sleep\n");
		return (1);
	}
	data->philo_count = ft_atoi(argv[1]);
	data->die_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sleep_t = ft_atoi(argv[4]);
	if (data->die_t <= 0 || data->eat_t <= 0 || data->sleep_t <= 0)
	{
		printf("time must be a positive integer\n");
		return (1);
	}
	if (data->philo_count < 1 || data->philo_count > 200)
	{
		printf("num_of_philo must be from 1 to 200\n");
		return (1);
	}
	data->wait_for_start = 1;
	return (0);
}

void	*routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	// printf("data philo count: %i\n", data->philo_count);
	printf("waiting...\n");
	while (data->wait_for_start)
		continue ;
	printf("finished waiting\n");
	return (0);
}

/*
 *	creates the threads, one for each philosopher.
 *	creates the forks, including their mutexes.
 *	creates the mutex for each philosopher's time.
 */
int	create_threads(pthread_t **threads, int philo_count, t_data *data)
{
	int	i;

	i = 0;
	*threads = malloc(sizeof(**threads) * philo_count);
	if (*threads == NULL)
		return (1);
	while (i < philo_count)
	{
		if (pthread_create(&(*threads)[i], NULL, &routine, data))
			return (2);
		i++;
	}
	i = 0;
	return (0);
}

int	create_forks(t_data *data)
{
	data->forks = malloc(sizeof(*data->forks) * data->philo_count);
	if (data->forks == NULL)
		return (1);
	memset(data->forks, 0, sizeof(*(data->forks)) * data->philo_count);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;
	int	i = 0;

	threads = NULL;
	if (init(&data, argc, argv) != 0)
		return (1);
	// printf("count: %i\ndie: %i\neat: %i\nsleep: %i\n", data.philo_count, data.die_t, data.eat_t, data.sleep_t);
	if (create_forks(&data) != 0)
		return (2);
	while (i < data.philo_count)
	{
		printf("%d %d\n", i, data.forks[i]);
		i++;
	}
	if (create_threads(&threads, data.philo_count, &data) != 0)
	{
		printf("failed to create threads\n");
		return (3);
	}
	// sleep(2);
	data.wait_for_start = 0;
	i = 0;
	while (i < data.philo_count)
	{
		printf("test 1\n");
		if (pthread_join(threads[i], NULL) != 0)
			return (3);
		printf("test 2\n");
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