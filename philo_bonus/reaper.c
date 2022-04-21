/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:45:50 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 19:14:02 by mmeising         ###   ########.fr       */
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
	waitpid(data->threads_watch[philo->philo_num - 1], &ret, 0);
	if ( WIFEXITED(ret) ) {
        const int es = WEXITSTATUS(ret);
        printf("exit status was %d\n", es);
    }

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
