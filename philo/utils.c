/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:15:11 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 03:09:14 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_handle(t_data *data, t_error err)
{
	data->err_code = err;
	if (err == WRONG_ARGC)
	{
		printf("usage (time in ms): ./philo num_of_philo time_to_die ");
		printf("time_to_eat time_to_sleep\n");
	}
	else if (err == MALLOC_FAILED)
		printf("malloc failed\n");
	else if (err == TIME_NOT_POSITIVE)
		printf("time must be a positive integer\n");
	else if (err == WRONG_PHILO_COUNT)
		printf("num_of_philo must be from 1 to 200\n");
	else if (err == FAILED_CREATE_FORKS)
		printf("create_forks failed\n");
	else if (err == FAILED_CREATE_THREADS)
		printf("failed to create threads\n");
	else if (err == FAILED_PTHREAD_JOIN)
		printf("pthread_join failed\n");
	return (err);//maybe need to typecast to int
}

void	print_stat(t_philo *philo, t_data *data, t_status stat)
{
	if (stat == EAT)
		printf("%li %i is eating\n", timestamp(data), philo->philo_num);
	else if (stat == SLEEP)
		printf("%li %i is sleeping\n", timestamp(data), philo->philo_num);
	else if (stat == THINK)
		printf("%li %i is thinking\n", timestamp(data), philo->philo_num);
	else if (stat == FORK)
		printf("%li %i grabbed a fork\n", timestamp(data), philo->philo_num);
}

/*
 *	returns input (string representation of number) as integer value.
 */
int	ft_atoi(const char *str)
{
	long long int	nb;
	int				i;
	int				sign;

	nb = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb < 0 && sign == -1)
			return (0);
		if (nb < 0 && sign == 1)
			return (-1);
		i++;
	}
	return (sign * nb);
}
