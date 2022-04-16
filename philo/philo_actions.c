/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:37:00 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 02:13:51 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	philo_eat(t_philo *philo, t_data *data)
// {
	
// }

void	philo_sleep(t_philo *philo, t_data *data)
{
	printf("%li %i is sleeping\n", timestamp(data), philo->philo_num);
	ft_sleep(data->sleep_t);
}

void	philo_think(t_philo *philo, t_data *data)
{
	printf("%li %i is thinking\n", timestamp(data), philo->philo_num);
}
