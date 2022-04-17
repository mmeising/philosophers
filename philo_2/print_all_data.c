/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:08:15 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 22:29:48 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data *data)
{
	printf(GREEN"DATA\n\n"RESET);
	printf("philo_count\t%i\ndie_time\t%li\neat_time\t%li\nsleep_time\t%li\n",
		data->philo_count, data->die_time, data->eat_time, data->sleep_time);
	if (data->min_eat_count)
		printf("min_eat_count: %li\n", data->min_eat_count);
	printf("\n");
}

void	print_philo_num(t_philo **philos, int num)
{
	int	i;

	i = num - 1;
	printf(YELLOW"philo_num\t%i\n"RESET"forks\t\t%i %i\neat_time\t%li\n\n",
		philos[i]->philo_num, philos[i]->fork_l, philos[i]->fork_r,
		philos[i]->eat_time);
}

void	print_all_philos(t_data *data, t_philo **philos)
{
	int	i;

	printf(YELLOW"PHILOS\n\n"RESET);
	i = 0;
	while (i < data->philo_count)
	{
		print_philo_num(philos, i + 1);
		i++;
	}
}

void	print_all_data(t_data *data, t_philo **philos)
{
	print_data(data);
	print_all_philos(data, philos);
	// print_philo_num(philos, 3);
}
