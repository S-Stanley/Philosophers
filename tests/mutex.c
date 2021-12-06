/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 01:59:09 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/06 02:20:56 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int				g_mails = 0;
pthread_mutex_t	g_mutex;

void	*increment(void *arg)
{
	unsigned int	i;

	(void)arg;
	i = 0;
	while (i < 100000)
	{
		i++;
		pthread_mutex_lock(&g_mutex);
		g_mails++;
		pthread_mutex_unlock(&g_mutex);
	}
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_mutex_init(&g_mutex, NULL);
	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread1, NULL, increment, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&g_mutex);
	printf("%d\n", g_mails);
	return (0);
}
