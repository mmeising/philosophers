/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:45:50 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 21:45:59 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch(void *arg)
{
	t_comb	*comb;
	t_data	*data;
	t_philo *philo;
	int		ret;

	comb = (t_comb *)arg;
	data = comb->data;
	philo = comb->philo;
	free(comb);
	printf("waiting on philo %i\n", philo->philo_num);
	waitpid(data->pids[philo->philo_num - 1], &ret, 0);
	printf("finished waiting on philo %i\n", philo->philo_num);
	if ( WIFEXITED(ret) ) {
        const int es = WEXITSTATUS(ret);
        printf(RED"exit status was %d\n"RESET, es);
    }
	printf(YELLOW"watch's end\n"RESET);
	return (NULL);
}

void	reaper(t_data *data, t_philo **philos)
{
	t_comb	*comb;
	int		i;

	i = 0;
	while (i < data->philo_count)
	{
		comb = ft_calloc(1, sizeof(t_comb));
		if (comb == NULL)
			return ;
		comb->data = data;
		comb->philo = philos[i];
		pthread_create(&(data->threads_watch[i]), NULL, watch, comb);
		i++;
	}

}
