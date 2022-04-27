/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:23:08 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 00:30:47 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_fail(t_status err)
{
	if (err == WRONG_ARGC)
	{
		printf("usage: ./philo <num_of_philos> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> [(optional)min_eat_times]\n");
	}
	else if (err == WRONG_INTS)
	{
		printf("input arguments must be positive ints only!\n");
	}
	return (err);
}

/*
 *	exits with error message if program was executed in a wrong way
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

/*
 *	puts input variables into data struct
 */
void	save_input(t_data **data, char **argv)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (*data == NULL)
		ft_exit(NULL, NULL, MALLOC_FAIL);
	(*data)->philo_count = ft_atoi(argv[1]);
	(*data)->die_time = ft_atoi(argv[2]);
	(*data)->eat_time = ft_atoi(argv[3]);
	(*data)->sleep_time = ft_atoi(argv[4]);
	(*data)->ate_enough = 0;
	if (argv[5])
		(*data)->ate_enough = ft_atoi(argv[5]);
}
