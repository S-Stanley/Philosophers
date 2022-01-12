/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:55:49 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/12 23:08:55 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_mutex(pthread_mutex_t *forks, unsigned int nbr_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nbr_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
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
