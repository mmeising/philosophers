/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sweeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:03:33 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 20:06:18 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sweeper(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->threads_watch[i], NULL);
		i++;
	}
	printf("all watcher threads finished!\n");
	(void)philos;
}
