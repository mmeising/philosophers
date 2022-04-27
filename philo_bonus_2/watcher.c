/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 22:05:02 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/28 01:06:32 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ate_count_plus(t_data *data)
{
	sem_wait(data->ate_enough_lock);
	data->ate_enough++;
	sem_post(data->ate_enough_lock);
}

void	philo_died(t_data *data, t_philo **philos, int i)
{
	int	j;

	sem_wait(data->running_lock);
	if (data->running == true)
	{
		printf(RED"%li %i died\n"RESET, ft_timestamp(data), philos[i]->philo_num);
		data->running = false;
		j = 0;
		while (j < data->philo_count)
		{
			if (i != j)
				kill(data->pids[j], SIGKILL);
			j++;
		}
	}
	sem_post(data->running_lock);
}

void	*routine(void *arg)
{
	t_data *data;
	t_philo **philos;
	int		i;
	int		ret;
	int		exit_stat;

	uncomb(&data, &philos, &i, arg);
	waitpid(data->pids[i], &ret, 0);
	if (WIFEXITED(ret))
	{
		exit_stat = WEXITSTATUS(ret);
		if (exit_stat == ATE_ENOUGH)
			ate_count_plus(data);
		else if (exit_stat == DEAD)
			philo_died(data, philos, i);
	}
	return (NULL);
}

void	watcher(t_data *data, t_philo **philos)
{
	t_comb	*comb;
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		comb = ft_calloc(1, sizeof(t_comb));
		if (comb == NULL)
			ft_exit(&data, &philos, MALLOC_FAIL);
		comb->data = data;
		comb->philos = philos;
		comb->i = i;
		if (pthread_create(&(data->watch_th[i]), NULL, routine, comb) != 0)
			ft_exit(&data, &philos, THREAD_FAIL);
		i++;
	}
}
