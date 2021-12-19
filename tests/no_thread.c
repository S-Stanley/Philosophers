/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:29:50 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/19 15:16:14 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define ONE_SECOND	1000000
#define ONE_MINI_SECOND 1000
#define EATING		0
#define SLEEPING	1
#define THINKING	2
#define TRUE		1
#define TIME_TO_DIE	5000

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

void	what_to_do(int thread_nb)
{
	if ((thread_nb % 2) == 0)
	{
		action(EATING, thread_nb);
		action(SLEEPING, thread_nb);
		action(THINKING, thread_nb);
	}
	else
	{
		action(SLEEPING, thread_nb);
		action(THINKING, thread_nb);
		action(EATING, thread_nb);
	}
}

long int	setup_total(void)
{
	long int		total;
	struct timeval	time;

	total = 0;
	total = 0;
	gettimeofday(&time, NULL);
	total = total + time.tv_usec;
	return (total);
}

void	*philo_died(void *arg, int thread_nb)
{
	printf("Philo %d just died\n", thread_nb);
	exit(0);
	return (arg);
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
		total = setup_total();
		tmp = total;
		what_to_do(*thread_nb);
		gettimeofday(&time, NULL);
		total = total + time.tv_usec;
		printf("** Philo %d took %lu %lu (minisecond) from %u**\n", *thread_nb, (total % tmp) / ONE_MINI_SECOND, (total % tmp), TIME_TO_DIE);
		if ((total % tmp) > TIME_TO_DIE)
			return (philo_died(arg, *thread_nb));
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
