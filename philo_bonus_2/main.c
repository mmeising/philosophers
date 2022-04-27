/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:04:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 00:38:52 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philos;

	check_input(argc, argv);
	save_input(&data, argv);
	init_data(data);
	init_philos(data, &philos);
	init_idents(data, philos);
	init_locks(data, philos);
	init_processes(data,philos);
	watcher(data, philos);
	ft_sleep(1000);
	data->ms_start = ft_get_time();
	sem_post(data->start_lock);
	sweeper(data, philos);
	ft_exit(&data, &philos, 0);
}
