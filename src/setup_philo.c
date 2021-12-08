/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:56:52 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/08 22:18:52 by sserbin          ###   ########.fr       */
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

void	*routine(void	*arg)
{
	printf("new philo thread created");
	return (arg);
}

void	create_thread_and_join_for_philo(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		pthread_create(&philo->philo, NULL, routine, NULL);
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
