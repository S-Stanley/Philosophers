/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:11:14 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 14:51:32 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// int	g_global;

void	*routine(void	*arg)
{
	t_philo			*philo;
	t_prog			prog;
	t_routine		*root;

	pthread_mutex_lock(&g_mutex);
	g_global++;
	// printf("%d\n", g_global);
	root = (t_routine *)arg;
	prog = root->prog;
	philo = root->this_philo;
	printf("%d %s created\n", philo->id, philo->name);
	pthread_mutex_unlock(&g_mutex);
	return (arg);
}
