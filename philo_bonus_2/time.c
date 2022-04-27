/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:10:15 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/27 23:19:35 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_timestamp(t_data *data)
{
	long	timestamp;

	timestamp = ft_get_time() - data->ms_start;
	return (timestamp);
}

void	ft_sleep(long ms_time)
{
	long	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < ms_time)
		usleep(100);
}
