/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:31:48 by mmeising          #+#    #+#             */
/*   Updated: 2022/05/01 23:00:06 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	need to add all the freeing stuff if pointers exist
 */
void	ft_exit(t_data **data, t_philo ***philos, t_status err)
{
	(void)data;
	(void)philos;
	// printf(YELLOW"error code from ft_exit is %i"RESET"\n", err);
	exit(err);
}
