/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:13:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 01:06:12 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*prot_sem_open(const char *name, int count)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0666, count));
}

void	uncomb(t_data **data, t_philo ***philos, int *i, void *arg)
{
	t_comb	*comb;

	comb = (t_comb *)arg;
	*data = comb->data;
	*philos = comb->philos;
	*i = comb->i;
	free(comb);
}

void	print_statement(t_data *data, t_philo *philo, t_status stat)
{
	sem_wait(data->running_lock);
	if (stat == FORK)
	{
		printf("%li %i has taken a fork\n", ft_timestamp(data),
			philo->philo_num);
	}
	else if (stat == EAT)
	{
		printf("%li %i is eating\n", ft_timestamp(data), philo->philo_num);
	}
	else if (stat == SLEEP)
	{
		printf("%li %i is sleeping\n", ft_timestamp(data), philo->philo_num);
	}
	else if (stat == THINK)
	{
		printf("%li %i is thinking\n", ft_timestamp(data), philo->philo_num);
	}
	sem_post(data->running_lock);
}

