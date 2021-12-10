/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:09:48 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 19:10:15 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*give_name(const unsigned int id)
{
	if (id == 0)
		return ("Aristote");
	if (id == 1)
		return ("Kant");
	if (id == 2)
		return ("Platon");
	if (id == 3)
		return ("Socrate");
	if (id == 4)
		return ("Nietzsche");
	if (id == 5)
		return ("Descartes");
	if (id == 6)
		return ("Confucius");
	if (id == 7)
		return ("Marx");
	if (id == 8)
		return ("Sarte");
	if (id == 9)
		return ("Epicure");
	return ("Aristote");
}

t_philo	*add_philo(int id, char *name, t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*new;

	new = malloc(sizeof(t_philo));
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
		i++;
	}
	return (philo);
}

t_root	*create_new_root(t_philo *philo, pthread_mutex_t *mutex)
{
	t_root	*root;

	root = malloc(sizeof(t_root));
	root->name = philo->name;
	root->id = philo->id;
	root->g_mutex = mutex;
	return (root);
}

void	setup_philo_routine(pthread_mutex_t *g_mutex, t_philo *philo)
{
	t_root			*root;
	t_philo			*tmp;

	root = NULL;
	tmp = philo;
	while (philo)
	{
		root = create_new_root(philo, g_mutex);
		pthread_create(&philo->thread, NULL, routine, root);
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}	
}
