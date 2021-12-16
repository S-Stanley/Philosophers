/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:29:50 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/16 23:01:52 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#define ONE_SECOND	1000000
#define ONE_MINI_SECOND 1000
#define EATING		0
#define SLEEPING	1
#define THINKING	2

pthread_mutex_t	g_mutex;

void	action(int action, unsigned int id)
{
	if (action == EATING)
	{
		printf("philo %d is eating\n", id);
		usleep(ONE_MINI_SECOND * 2);
	}
	else if (action == SLEEPING)
	{
		printf("philo %d is sleeping\n", id);
		usleep(ONE_MINI_SECOND * 2);
	}
	else
	{
		printf("philo %d is thinking\n", id);
	}
}

void	*routine(void *arg)
{
	unsigned int	iter;
	unsigned int	*thread_nb;
	struct timeval	time;
	long int		total;
	long int		tmp;

	pthread_mutex_lock(&g_mutex);
	iter = 0;
	thread_nb = (unsigned int *)arg;
	while (iter < 4)
	{
		total = 0;
		gettimeofday(&time, NULL);
		total = total + time.tv_usec;
		tmp = total;
		action(EATING, *thread_nb);
		action(SLEEPING, *thread_nb);
		action(THINKING, *thread_nb);
		gettimeofday(&time, NULL);
		total = total + time.tv_usec;
		printf("** Philo %d took %lu %lu (minisecond) to made iteration %d**\n",
			*thread_nb, (total % tmp) / ONE_MINI_SECOND, (total % tmp), iter);
		iter++;
	}
	pthread_mutex_unlock(&g_mutex);
	return (arg);
}

int	main(void)
{
	unsigned int	nb;
	pthread_t		threads[2];
	unsigned int	id[] = {1, 2};

	pthread_mutex_init(&g_mutex, NULL);
	nb = 0;
	while (nb < 2)
	{
		pthread_create(&threads[nb], NULL, routine, &id[nb]);
		nb++;
	}
	nb = 0;
	while (nb < 2)
	{
		pthread_join(threads[nb], NULL);
		nb++;
	}
	pthread_mutex_destroy(&g_mutex);
	return (0);
}
