/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 01:00:20 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/04 01:33:47 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

BOOL	check_fork(t_dishes *fork, int nb)
{
	int		count;

	count = 0;
	while (fork)
	{
		fork = fork->next;
		count++;
	}
	return (count == nb);
}

t_dishes	*init_mutex(int nb)
{
	int			i;
	t_dishes	*fork;
	t_dishes	*tmp;

	fork = NULL;
	i = 0;
	while (i < nb)
	{
		fork = add_fork(fork, i);
		i++;
	}
	if (!check_fork(fork, nb))
		return (NULL);
	tmp = fork;
	while (fork)
	{
		pthread_mutex_init(&fork->fork, NULL);
		fork = fork->next;
	}
	return (tmp);
}

void	destroy_mutex(t_dishes *fork)
{
	t_dishes	*tmp;

	while (fork)
	{
		tmp = fork->next;
		pthread_mutex_destroy(&fork->fork);
		free(fork);
		fork = tmp;
	}
}

void	free_dishes(t_dishes *fork)
{
	t_dishes	*tmp;

	while (fork)
	{
		tmp = fork->next;
		free(fork);
		fork = tmp;
	}
}
