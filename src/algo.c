/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:11:14 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/09 20:37:38 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*routine(void	*arg)
{
	t_philo			*philo;
	pthread_mutex_t	*mutex;

	philo = (t_philo *)arg;
	mutex = philo->mutex;
	pthread_mutex_lock(mutex);
	printf("%d %s created\n", philo->id, philo->name);
	pthread_mutex_unlock(mutex);
	return (arg);
}
