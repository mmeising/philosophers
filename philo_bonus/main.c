/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:08:05 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/20 23:47:35 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	checks input count and that all arguments are positive integers.
 */
void	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		exit(args_fail(WRONG_ARGC));
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) <= 0)
			exit(args_fail(WRONG_INTS));
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				exit(args_fail(WRONG_INTS));
			j++;
		}
		i++;
	}
}

//	create all philos in main, create start semaphore with 0, post 1 when ready to start.
//	instead of reapers, check if philo should die in the ft_sleep loop condition. exit if dead.
//	check times_eaten when leaving the philo_eat function.
//	main at the end will create watcher threads, one for each philo. they will waitpid.
//	the one which returns will print that its philo number died at that timestamp.
//	then send kill signal to all forks?
//	bool to print when one philo died, set to true after first death message printed,
//	no more death messages printed after that.

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philos;

	check_input(argc, argv);
	init_data(&data, argv);
	init_philos(data, &philos);
	init_idents(data);
	init_locks(data);
	init_processes(data, philos);
	reaper(data, philos);//needs to set up and then wait for start_lock
	sem_post_n(data->start_lock, data->philo_count * 2);// times 2 for processes and reaper checkers to start
}
