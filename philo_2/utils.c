/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 22:45:26 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/18 00:29:20 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	writes len bytes of value c (converted to unsigned char) to string str
 */
void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = str;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

/*
 *	mallocs an array, sets bytes to \0 and returns the array
 */
void	*ft_calloc(int count, int size)
{
	void			*ptr;
	unsigned int	i;

	if (count <= 0 || size <= 0)
		return (NULL);
	i = (count * size);
	ptr = malloc(i);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, '\0', count * size);
	return (ptr);
}

/*
 *	returns input (string representation of number) as long value.
 *	has to return long to be able to compare it against INT_MAX.
 */
long	ft_atoi(const char *str)
{
	long	nb;
	int		i;
	int		sign;

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

/*
 *	prints timestamp, philosopher number and its status.
 *
 *	only prints if the simulation should still be runnning to protect from
 *	any prints after a philosopher died.
 */
void	print_status(t_data *data, t_philo *philo, t_status status)
{
	pthread_mutex_lock(&(data->running_lock));
	if (data->running == false)
	{
		pthread_mutex_unlock(&(data->running_lock));
		return ;
	}
	if (status == EAT)
		printf("%li %i is eating\n", timestamp(data), philo->philo_num);
	else if (status == SLEEP)
		printf("%li %i is sleeping\n", timestamp(data), philo->philo_num);
	else if (status == THINK)
		printf("%li %i is thinking\n", timestamp(data), philo->philo_num);
	else if (status == FORK)
		printf("%li %i has taken a fork\n", timestamp(data), philo->philo_num);
	pthread_mutex_unlock(&(data->running_lock));
}

/*
 *	prints the error messages for wrong input count or
 *	input that is no positive integer.
 */
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
	return (EXIT_FAILURE);
}
