/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:40:31 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/08 16:37:00 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_philo	*add_philo(int id, t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = id + 1;
	new->ate = 0;
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
		philo = add_philo((int)i, philo);
		if (!philo)
		{
			free_philo(philo);
			return (NULL);
		}
		i++;
	}
	return (philo);
}
