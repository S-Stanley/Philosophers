/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 21:07:26 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*routine(void *arg)
{
	t_root	*root;

	root = (t_root *)arg;
	if (pthread_mutex_lock(root->g_mutex) != 0)
		return (free_root_and_return(root));
	printf("creating philo %s with id %d\n", root->name, root->id);
	if (pthread_mutex_unlock(root->g_mutex) != 0)
		return (free_root_and_return(root));
	return (free_root_and_return(root));
}
