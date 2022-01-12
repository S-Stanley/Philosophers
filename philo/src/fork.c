/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:08:18 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/12 01:12:11 by sserbin          ###   ########.fr       */
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
	if (!print_something(data, 0))
		return ;
	pthread_mutex_lock(&couvert.right->fork);
	if (!print_something(data, 0))
		return ;
}

void	unlock_fork(t_data *data)
{
	t_couvert		couvert;

	couvert = get_philo_fork(data->id, data->fork);
	pthread_mutex_unlock(&couvert.left->fork);
	pthread_mutex_unlock(&couvert.right->fork);
}

t_dishes	*add_fork(t_dishes *fork, unsigned int i)
{
	t_dishes	*new;
	t_dishes	*tmp;

	new = malloc(sizeof(t_dishes));
	if (!new)
		return (fork);
	new->id = i;
	new->fork = malloc(sizeof(pthread_mutex_t));
	new->next = NULL;
	if (!fork)
		return (new);
	tmp = fork;
	while (fork->next)
		fork = fork->next;
	fork->next = new;
	return (tmp);
}
