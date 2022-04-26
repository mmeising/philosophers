/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:08:05 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 20:08:31 by mmeising         ###   ########.fr       */
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

	printf("main check:\n");
	check_input(argc, argv);
	printf("main data:\n");
	init_data(&data, argv);
	printf("main philos:\n");
	init_philos(data, &philos);
	printf("main idents:\n");
	init_idents(data);
	printf("main locks:\n");
	init_locks(data);
	printf("main processes:\n");
	init_processes(data, philos);
	printf("main reaper:\n");
	reaper(data, philos);//needs to set up and then wait for start_lock
	// sem_post_n(data->start_lock, data->philo_count * 2);// times 2 for processes and reaper checkers to start
	//	or rather start lock with 0, post1 when starting. every waiting process will also post1 afterwards,
	//	which should start up every single process
	printf("main sweeper:\n");
	sweeper(data, philos);//kill all processes and free every non-NULL pointer
	//maybe also reuse the start_lock so sweeper only starts when a reaper detects process end.
}
//00660 as sem_open mode flag (user and group have read and write permission)
