/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:32:29 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/26 18:18:32 by mmeising         ###   ########.fr       */
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
		usleep(100);
}

/*
 *	sleeps for ms_time milliseconds, checking every loop if philo didn't starve.
 *	if philo starved, sets stat to DEAD and returns DEAD.
 *	if it finished waiting without a death, returns 0.
 */
t_status	ft_sleep_check(t_data *data, t_philo *philo, long ms_time)
{
	long	start_time;

	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < ms_time)
	{
		if (philo->eat_time + data->die_time < timestamp(data))
		{
			philo->stat = DEAD;
			printf(RED"%li %i died. from sleepcheck\n"RESET, timestamp(data), philo->philo_num);
			return (DEAD);
		}
		else
			usleep(100);
	}
	return (0);
}

/*
 *	returns the current timestamp in ms since start
 */
long	timestamp(t_data *data)
{
	long	timestamp;

	timestamp = ft_get_time() - data->ms_start;
	return (timestamp);
}
