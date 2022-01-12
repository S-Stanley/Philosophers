/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:48:31 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/12 01:41:03 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define NB_PHILO	4

typedef struct s_data {
	int				id;
	pthread_mutex_t	*forks;
}	t_data;

long int	get_time(struct timeval time)
{
	struct timeval	now;
	long int		max;

	max = 999999;
	gettimeofday(&now, NULL);
	if (now.tv_sec == time.tv_sec)
		return ((now.tv_usec - time.tv_usec) / 1000);
	else
		return ((
				((max - time.tv_usec) + now.tv_usec)
				+ ((now.tv_sec - time.tv_sec -1) * max)) / 1000);
}

void	eating(t_data *data, struct timeval *start_time)
{
	pthread_mutex_lock(&data->forks[data->id - 1]);
	printf("%ld philo %d has taken a fork\n",
		get_time(*start_time), data->id);
	pthread_mutex_lock(&data->forks[data->id]);
	printf("%ld philo %d has taken a fork\n",
		get_time(*start_time), data->id);
	printf("**** philo %d max %ld ****\n", data->id, get_time(*start_time));
	gettimeofday(start_time, NULL);
	printf("%ld philo %d is eating\n", get_time(*start_time), data->id);
	usleep(200 * 1000);
	pthread_mutex_unlock(&data->forks[data->id - 1]);
	pthread_mutex_unlock(&data->forks[data->id]);
}

void	*routine(void *arg)
{
	t_data			*data;
	struct timeval	start_time;

	data = (t_data *)arg;
	gettimeofday(&start_time, NULL);
	if (data->id % 2)
		usleep(200 * 1000);
	while (1)
	{
		eating(data, &start_time);
		printf("%ld philo %d is sleeping\n", get_time(start_time), data->id);
		usleep(200 * 1000);
		printf("%ld philo %d is thinking\n", get_time(start_time), data->id);
	}
	free(arg);
	return (arg);
}

void	init_mutex(pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	destroy_mutex(pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < NB_PHILO)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	main(void)
{
	pthread_t		threads[NB_PHILO];
	void			*forks;
	int				i;
	t_data			*data;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * NB_PHILO);
	init_mutex(forks);
	while (i < NB_PHILO)
	{
		data = malloc(sizeof(t_data));
		data->id = i + 1;
		data->forks = forks;
		pthread_create(&threads[i], NULL, routine, data);
		i++;
	}
	i = 0;
	while (i < NB_PHILO)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	destroy_mutex(forks);
	return (0);
}
