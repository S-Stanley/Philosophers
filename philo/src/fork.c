/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:07:37 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:08:08 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

void	lock_fork(t_root root)
{
	t_couvert		couvert;

	couvert = get_philo_fork(root.id, root.fork);
	pthread_mutex_lock(&couvert.left->fork);
	pthread_mutex_lock(&couvert.right->fork);
}

void	unlock_fork(t_root root)
{
	t_couvert		couvert;

	couvert = get_philo_fork(root.id, root.fork);
	pthread_mutex_unlock(&couvert.left->fork);
	pthread_mutex_unlock(&couvert.right->fork);
}
