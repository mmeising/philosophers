/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 23:12:36 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/18 00:17:15 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	checks input count and if all arguments are positive integers.
 */
int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (args_fail(WRONG_ARGC));
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) <= 0)
			return (args_fail(WRONG_INTS));
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (args_fail(WRONG_INTS));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philos;

	if (check_input(argc, argv))
		return (EXIT_FAILURE);
	if (init_data(&data, argv))
		return (EXIT_FAILURE);
	if (init_philos(data, &philos))
		return (EXIT_FAILURE);
	if (init_mutexes(data))
		return (EXIT_FAILURE);
	if (init_threads(data, philos))
		return (EXIT_FAILURE);
	data->ms_start = ft_get_time();
	data->wait_for_start = false;
	reaper(data, philos);
	sweeper(data, philos);
	return (0);
}
