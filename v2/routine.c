/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 19:09:33 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*routine(void *arg)
{
	t_root	*root;

	root = (t_root *)arg;
	pthread_mutex_lock(root->g_mutex);
	printf("creating philo %s with id %d\n", root->name, root->id);
	pthread_mutex_unlock(root->g_mutex);
	free(root);
	return (arg);
}
