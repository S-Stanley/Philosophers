/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:29:50 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/18 14:43:38 by sserbin          ###   ########.fr       */
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
#define TRUE		1
#define TIME_TO_DIE	7000

pthread_mutex_t	g_mutex;

void	action(int action, unsigned int id)
{
	if (action == EATING)
	{
		pthread_mutex_lock(&g_mutex);
		printf("philo %d is eating\n", id);
		usleep(ONE_MINI_SECOND * 2);
		pthread_mutex_unlock(&g_mutex);
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
	unsigned int	*thread_nb;
	struct timeval	time;
	long int		total;
	long int		tmp;

	thread_nb = (unsigned int *)arg;
	while (TRUE)
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
		printf("** Philo %d took %lu %lu (minisecond) from %u**\n",
			*thread_nb, (total % tmp) / ONE_MINI_SECOND, (total % tmp), TIME_TO_DIE);
		if ((total % tmp) > TIME_TO_DIE)
		{
			printf("Philo %d just died\n", *thread_nb);
			return (arg);
		}
	}
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
