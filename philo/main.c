/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:31:38 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 22:21:28 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_comb	*comb;
	t_philo *philo;
	t_data	*data;

	// while (true) ;
	comb = (t_comb *)arg;
	philo = comb->philo;
	data = comb->data;
	free(comb);
	while (data->wait_for_start == true)
		continue ;
	// printf(GREEN"my philo_num is: %i\n"RESET, philo->philo_num);
	// if (philo->philo_num % 2 == 0)
	// 	philo_sleep(philo, data);
	printf(GREEN"from philo:\taddr: %p, philo_num: %i forks: %i %i\n"RESET, philo, philo->philo_num, philo->fork_l, philo->fork_r);
	
	// printf("philo %i's l&r forks are: %i %i\n", philo->philo_num, philo->fork_l, philo->fork_r);
	// while (philo->status != DEAD)
	// {
	// 	philo_eat(philo, data);
	// 	philo_sleep(philo, data);
	// 	philo_think(philo, data);
	// }
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

//			!!!				!!!				!!!					!!!
//		DATA INSIDE PHILO[philo_count / 2] gets corrupted		???
//			!!!				!!!				!!!					!!!
//				maybe wrong malloc somewhere along the way
int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		**philo;
	int			i;

	i = 0;
	data = malloc(sizeof(*data));
	if (data == NULL)
		return (err_handle(data, MALLOC_FAILED));
	if (init_data(data, argc, argv) != 0)
		return (data->err_code);
	philo = (t_philo **)calloc(sizeof(t_philo *), data->philo_count);
	if (philo == NULL)
		return (err_handle(data, MALLOC_FAILED));
	while (i < data->philo_count)
	{
		philo[i] = (t_philo *)calloc(sizeof(t_philo), 1);
		if (philo == NULL)
			return (err_handle(data, MALLOC_FAILED));
		i++;
	}
	// i = 0;//start of test
	// while (i < data->philo_count)
	printf(PURPLE"in main after malloc:\t%p\n"RESET, philo[0]);//end of test
	if (init_mutex(data) != 0)
		return (data->err_code);
	if (init_threads(data, philo) != 0)
		return (data->err_code);
	data->ms_start = get_time();
	data->wait_for_start = false;
	i = 0;
	while (i < data->philo_count)
	{
		printf(YELLOW"from main:\taddr: %p, i: %i philo_num: %i forks: %i %i\n"RESET, (philo[i]), i, philo[i]->philo_num, philo[i]->fork_l, philo[i]->fork_r);
		i++;
	}
	// reaper(philo, data);
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