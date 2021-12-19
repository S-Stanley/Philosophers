/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:29:50 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/19 16:01:59 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define ONE_SECOND		1000000
#define ONE_MINI_SECOND	1000
#define EATING			0
#define SLEEPING		1
#define THINKING		2
#define TIME_TO_DIE		410
#define TIME_TO_EAT		200
#define TIME_TO_SLEEP	200

#define FALSE			0
#define TRUE			1
#define BOOLEAN			unsigned int

pthread_mutex_t	g_mutex;

void	action(int action, unsigned int id)
{
	if (action == EATING)
	{
		pthread_mutex_lock(&g_mutex);
		printf("philo %d is eating\n", id);
		usleep(TIME_TO_SLEEP * ONE_MINI_SECOND);
		pthread_mutex_unlock(&g_mutex);
	}
	else if (action == SLEEPING)
	{
		printf("philo %d is sleeping\n", id);
		usleep(TIME_TO_EAT * ONE_MINI_SECOND);
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

struct timeval	get_timeval(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

BOOLEAN	check_philo_alive(struct timeval time, struct timeval tmp, int id)
{
	long int	max_value_usec;
	long int	iter_time;

	max_value_usec = 999999;
	if (time.tv_sec == tmp.tv_sec)
		iter_time = time.tv_usec - tmp.tv_usec;
	else
		iter_time = time.tv_usec + (max_value_usec - tmp.tv_usec);
	iter_time = iter_time / ONE_MINI_SECOND;
	printf("*Philo %d took %ld usec out of %d\n", id, iter_time, TIME_TO_DIE);
	if (iter_time > TIME_TO_DIE)
	{
		printf("Philo %d just died\n", id);
		return (FALSE);
	}
	return (TRUE);
}

void	*routine(void *arg)
{
	unsigned int	*thread_nb;
	struct timeval	time;
	struct timeval	tmp;

	thread_nb = (unsigned int *)arg;
	while (TRUE)
	{
		time = get_timeval();
		tmp = time;
		what_to_do(*thread_nb);
		gettimeofday(&time, NULL);
		time = get_timeval();
		if (!check_philo_alive(time, tmp, *thread_nb))
			return (arg);
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
