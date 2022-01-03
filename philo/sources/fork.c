/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:08:18 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/04 00:29:20 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_couvert	get_philo_fork(unsigned int id, t_dishes *fork)
{
	t_couvert	to_return;
	t_dishes	*tmp;
	int			copy_id;

	tmp = fork;
	copy_id = id;
	while (id > 0 && fork->next)
	{
		fork = fork->next;
		id--;
	}
	to_return.left = fork;
	if (fork->next)
	{
		fork = fork->next;
		to_return.right = fork;
	}
	else
		to_return.right = tmp;
	return (to_return);
}

void	lock_fork(t_data *data)
{
	t_couvert		couvert;

	couvert = get_philo_fork(data->id, data->fork);
	pthread_mutex_lock(&couvert.left->fork);
	pthread_mutex_lock(&couvert.right->fork);
}

void	unlock_fork(t_data *data)
{
	t_couvert		couvert;

	couvert = get_philo_fork(data->id, data->fork);
	pthread_mutex_unlock(&couvert.left->fork);
	pthread_mutex_unlock(&couvert.right->fork);
}
