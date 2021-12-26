/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:09:48 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:26:55 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_philo	*add_philo(int id, char *name, t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id;
	new->name = name;
	new->next = NULL;
	if (!philo)
		return (new);
	tmp = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = new;
	return (tmp);
}

t_philo	*setup_philo(t_arg arg)
{
	t_philo			*philo;
	unsigned int	i;

	philo = NULL;
	i = 0;
	while (i < arg.nbr_philo)
	{
		philo = add_philo((int)i, give_name(i), philo);
		if (!philo)
		{
			free_philo(philo);
			return (NULL);
		}
		i++;
	}
	return (philo);
}

t_root	*create_new_root(	t_philo *philo, t_arg arg, t_create_root pts)
{
	t_root	*root;

	root = malloc(sizeof(t_root));
	if (!root)
		return (NULL);
	root->name = philo->name;
	root->id = philo->id;
	root->g_mutex = pts.g_mutex;
	root->fork = pts.fork;
	root->arg = arg;
	root->philo = pts.start;
	root->stop = pts.stop;
	return (root);
}

t_create_root	setup_pts(	int *stop, pthread_mutex_t *g_mutex,
							t_philo *start, t_dishes *fork)
{
	t_create_root	to_return;

	to_return.fork = fork;
	to_return.g_mutex = g_mutex;
	to_return.start = start;
	to_return.stop = stop;
	return (to_return);
}

char	*setup_philo_routine(	pthread_mutex_t *g_mutex, t_philo *philo,
								t_dishes *fork, t_arg arg)
{
	t_root			*root;
	t_philo			*tmp;
	t_create_root	pts;

	root = NULL;
	pts = setup_pts(get_stop_value(), g_mutex, philo, fork);
	tmp = philo;
	while (philo)
	{
		root = create_new_root(philo, arg, pts);
		if (!root)
			return (NULL);
		if (pthread_create(&philo->thread, NULL, routine, root) != 0)
			return (free_root_and_return_null(root));
		philo = philo->next;
	}
	while (tmp)
	{
		if (pthread_join(tmp->thread, NULL) != 0)
			return (free_root_and_return_null(root));
		tmp = tmp->next;
	}
	return ("good");
}
