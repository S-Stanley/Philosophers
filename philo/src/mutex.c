/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:55:49 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 22:04:12 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

BOOL	init_mutex(pthread_mutex_t *forks, unsigned int nbr_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	destroy_mutex(pthread_mutex_t *forks, unsigned int nbr_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nbr_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
