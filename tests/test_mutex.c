/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:55:36 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 18:07:04 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_root {
	pthread_mutex_t	g_mutex;
	char			*name;
}	t_root;

void	*routine(void *arg)
{
	t_root	*root;

	root = (t_root *)arg;
	pthread_mutex_lock(&root->g_mutex);
	printf("%s\n", root->name);
	pthread_mutex_unlock(&root->g_mutex);
	return (arg);
}

int	main(void)
{
	pthread_t		threads[4];
	char			*names[] = {"Aristote", "Socrate", "Platon", "Kant", 0};
	unsigned int	i;
	t_root			root;

	pthread_mutex_init(&root.g_mutex, NULL);
	i = 0;
	while (names[i])
	{
		root.name = names[i];
		pthread_create(&threads[i], NULL, routine, &root);
		i++;
	}
	i = 0;
	while (names[i])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&root.g_mutex);
	return (0);
}
