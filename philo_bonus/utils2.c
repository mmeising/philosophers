/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:37:08 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/27 00:54:33 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sem_post_n(sem_t *sem, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_post(sem);
		printf("sem_posted\n");
		i++;
	}
}

void	print_status(t_data *data, t_philo *philo, t_status stat)
{
	sem_wait(data->running_lock);
	if (data->running == false)
	{
		sem_post(data->running_lock);
		return ;
	}
	if (stat == EAT)
		printf("%li %i is eating\n", timestamp(data), philo->philo_num);
	else if (stat == SLEEP)
		printf("%li %i is sleeping\n", timestamp(data), philo->philo_num);
	else if (stat == THINK)
		printf("%li %i is thinking\n", timestamp(data), philo->philo_num);
	else if (stat == FORK)
		printf("%li %i has taken a fork\n", timestamp(data), philo->philo_num);
	sem_post(data->running_lock);
}

sem_t	*wrapped_sem_open(const char *name, int count)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0666, count));
}

void	ate_count_plus(t_data *data)
{
	sem_wait(data->ate_lock);
	data->ate_enough_count++;
	sem_post(data->ate_lock);
}

//needs to send sigkill to all other philos to stop simulation (and free all stuff?)
void	philo_dead(t_data *data, t_philo **philos, int i)
{
	int	j;

	printf(RED"%li %i died. from philo_dead\n"RESET, timestamp(data), philos[i]->philo_num);
	j = 0;
	while (j < data->philo_count)
	{
		if (i != j)
			kill(data->pids[j], SIGKILL);
		j++;
	}
}
