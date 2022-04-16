/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:09:09 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 01:14:58 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reaper(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (true)
	{
		if (i == data->philo_count)
			i = 0;
		if (timestamp(data) > philos[i]->eat_time + data->die_time)
		{
			print_status(data, philos[i], DEAD);
			return ;
		}
		i++;
	}
}
