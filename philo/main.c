/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:31:38 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/14 21:23:15 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	wait_for_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->thread_id[i], NULL) != 0)
			return (err_handle(data, FAILED_PTHREAD_JOIN));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	*threads;

	threads = NULL;
	data = malloc(sizeof(*data));
	if (data == NULL)
		return (err_handle(data, MALLOC_FAILED));
	if (init_data(data, argc, argv) != 0)
		return (data->err_code);
	if (init_mutex(data) != 0)
		return (data->err_code);
	if (init_threads(data->philo_count, data) != 0)
		return (data->err_code);
	data->wait_for_start = false;
	if (wait_for_philos(data) != 0)
		return (data->err_code);
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