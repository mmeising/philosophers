/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:45:50 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/27 00:48:55 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch(void *arg)
{
	t_comb	*comb;
	t_data	*data;
	t_philo **philos;
	int		ret;
	int		i;

	comb = (t_comb *)arg;
	data = comb->data;
	philos = comb->philos;
	i = comb->i;
	free(comb);//need to use uncomb function here, too
	// printf("waiting on philo %i\n", philos[i]->philo_num);
	waitpid(data->pids[philos[i]->philo_num - 1], &ret, 0);
	// printf("finished waiting on philo %i\n", philos[i]->philo_num);
	if ( WIFEXITED(ret) )
	{
        const int es = WEXITSTATUS(ret);
		if (es == ATE_ENOUGH)
			ate_count_plus(data);
		else if (es == DEAD)
			philo_dead(data, philos, i);
		else
			printf("exit status was %d\n", es);
        // printf(RED"exit status was %d\n"RESET, es);
    }
	printf(RED"%li %i died. from watch\n"RESET, timestamp(data), philos[i]->philo_num);
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
		comb->philos = philos;
		comb->i = i;
		pthread_create(&(data->threads_watch[i]), NULL, watch, comb);
		i++;
	}

}
