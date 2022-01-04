/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 01:00:20 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/04 01:00:27 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
