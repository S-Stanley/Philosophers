/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:56:52 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 18:42:04 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_philo	*create_philo(unsigned int id, char *name)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		return (NULL);
	lst->id = id;
	lst->name = name;
	lst->next = NULL;
	return (lst);
}

t_philo	*push_back_philo(t_philo *lst, unsigned int id, char *name)
{
	t_philo	*new;
	t_philo	*tmp;

	new = create_philo(id, name);
	if (!new)
		exit_programme("Erreur malloc at create philo\n", lst);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}

void	create_thread_and_join_for_philo(t_prog prog, pthread_mutex_t *mutex)
{
	t_philo		*tmp;
	t_philo		*philo;
	t_routine	root;

	philo = prog.philo;
	tmp = philo;
	root.prog = prog;
	root.global = 0;
	(void)mutex;
	while (philo)
	{
		root.this_philo = philo;
		pthread_create(&philo->philo, NULL, routine, &root);
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		pthread_join(philo->philo, NULL);
		philo = philo->next;
	}
}

t_philo	*setup_philo(t_arg arg)
{
	unsigned int	i;
	t_philo			*lst;

	i = 0;
	lst = NULL;
	while (i < arg.nbr_philo)
	{
		lst = push_back_philo(lst, i, give_name(i));
		i++;
	}
	return (lst);
}
