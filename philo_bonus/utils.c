/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:18:06 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/20 23:07:31 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_count_for_malloc(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		nb *= -1;
		count++;
	}
	if (nb == 0)
		count++;
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

/*
 *	takes input integer n and returns (malloc'd) string representation of it
 */
char	*ft_itoa(int n)
{
	char	*string;
	int		count;
	long	nb;

	nb = n;
	count = ft_count_for_malloc(nb);
	string = (char *)malloc(sizeof(char) * (count + 1));
	if (!string)
		return (NULL);
	string[count--] = '\0';
	if (nb == 0)
		string[0] = '0';
	if (nb == 0)
		return (string);
	if (nb < 0)
		string[0] = '-';
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		string[count] = '0' + (nb % 10);
		nb = nb / 10;
		count--;
	}
	return (string);
}

// /*
//  *	writes len bytes of value c (converted to unsigned char) to string str
//  */
// void	*ft_memset(void *str, int c, size_t len)
// {
// 	size_t			i;
// 	unsigned char	*ptr;

// 	i = 0;
// 	ptr = str;
// 	while (i < len)
// 	{
// 		ptr[i] = (unsigned char)c;
// 		i++;
// 	}
// 	return (str);
// }

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
	memset(ptr, '\0', count * size);
	return (ptr);
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
	return (WRONG_INPUT);
}
