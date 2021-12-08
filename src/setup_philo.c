/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:56:52 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/08 22:00:49 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

t_philo	*setup_philo(t_arg arg)
{
	unsigned int	i;
	t_philo			*lst;

	i = 0;
	lst = NULL;
	while (i < arg.nbr_philo)
	{
		lst = push_back_philo(lst, i, "Aristote");
		i++;
	}
	return (lst);
}

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		tmp = philo->next;
		printf("%d %s\n", philo->id, philo->name);
		free(philo);
		philo = tmp;
	}
}
