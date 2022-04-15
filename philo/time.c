/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:40:11 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/16 00:45:25 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	returns time in ms
 */
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
 *	returns the current timestamp in ms since start
 */
long	timestamp(t_philo *philo)
{
	return (get_time() - philo->data->ms_start);
}

/*
 *	sleeps for time_ms milliseconds
 */
void	ft_sleep(long time_ms)
{
	long	start_time;

	start_time = get_time();
	while ((start_time + time_ms) > get_time())
		usleep(500);
}