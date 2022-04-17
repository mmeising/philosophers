/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 22:35:26 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/17 01:53:41 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	returns time in ms
 */
long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
 *	sleeps for ms_time milliseconds
 */
void	ft_sleep(long ms_time)
{
	long	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < ms_time)
		usleep(500);
}

/*
 *	returns the current timestamp in ms since start
 */
long	timestamp(t_data *data)
{
	long	timestamp;

	pthread_mutex_lock(&(data->ms_start_lock));
	timestamp = ft_get_time() - data->ms_start;
	pthread_mutex_unlock(&(data->ms_start_lock));
	return (timestamp);
}
