/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:22:55 by mmeising          #+#    #+#             */
/*   Updated: 2022/04/21 19:51:48 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(t_data **data, t_philo ***philos, t_status stat)
{
	// if (*data)
	// 	ft_free_data(data);
	// if (*philos)
	// 	ft_free_philos(philos);
	(void)data;
	(void)philos;
	if (stat == MALLOC_FAIL)
		return (10);
	else if (stat == *SEM_FAILED)
		return (11);
	else if (stat == DEAD)
		return (20);
	else if (stat == ATE_ENOUGH)
		return (21);
	else
		return (100);
}
