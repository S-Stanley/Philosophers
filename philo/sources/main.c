/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:52:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/02 18:45:47 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

#define TRUE 1
#define TIME_TO_SLEEP	200
#define TIME_TO_EAT		200
#define TIME_TO_DIE		450
#define NB_PHILO		2

typedef struct s_data {
	int				id;
	pthread_mutex_t	*mutex;
	long int		*time;
}	t_data;

long int	*create_timestamp(void);
t_data		*create_data(int id, long int *time, pthread_mutex_t *mutex);
void		*routine(void *arg);
void		eating(t_data *data, struct timeval time);
void		sleeping(t_data *data, struct timeval time);
void		thinking(t_data *data, struct timeval time);
long int	get_time(struct timeval time);

void	*routine(void *arg)
{
	t_data			*data;
	struct timeval	time;

	data = (t_data *)arg;
	while (TRUE)
	{
		gettimeofday(&time, NULL);
		pthread_mutex_lock(data->mutex);
		eating(data, time);
		sleeping(data, time);
		pthread_mutex_unlock(data->mutex);
		thinking(data, time);
	}
	free(arg);
}

long int	get_time(struct timeval time)
{
	struct timeval	now;
	long int		max;

	max = 999999;
	gettimeofday(&now, NULL);
	// printf("%ld %ld %ld %ld\n", now.tv_sec, now.tv_usec, time.tv_sec, time.tv_usec);
	if (now.tv_sec == time.tv_sec)
		return ((now.tv_usec - time.tv_usec) / 1000);
	else
		return (((max - time.tv_usec) + now.tv_usec) / 1000);
}

void	eating(t_data *data, struct timeval time)
{
	// *data->time = *data->time + get_time(time);
	printf("%ld philo %d is eating\n", *data->time + get_time(time), data->id);
	usleep(1000 * TIME_TO_EAT);
	// *data->time = *data->time + get_time(time);
	printf("%ld philo %d dropped fork\n", *data->time + get_time(time), data->id);
}

void	sleeping(t_data *data, struct timeval time)
{
	// *data->time = *data->time + get_time(time);
	printf("%ld philo %d is slepping %ld\n", *data->time + get_time(time), data->id, get_time(time));
	usleep(1000 * TIME_TO_SLEEP);
}

void	thinking(t_data *data, struct timeval time)
{
	// *data->time = *data->time + get_time(time);
	printf("%ld philo %d is thinking\n", *data->time + get_time(time), data->id);
}

t_data	*create_data(int id, long int *time, pthread_mutex_t *mutex)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->id = id;
	data->time = time;
	data->mutex = mutex;
	return (data);
}

long int	*create_timestamp(void)
{
	long int	*time;

	time = malloc(sizeof(long int));
	time[0] = 0;
	return (time);
}

int	main(void)
{
	int				i;
	pthread_t		threads[NB_PHILO];
	long int		*time;
	pthread_mutex_t	mutex;

	time = create_timestamp();
	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < NB_PHILO)
		pthread_create(&threads[i], NULL, routine, create_data(i, time, &mutex));
	i = -1;
	while (++i < NB_PHILO)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&mutex);
	free(time);
	return (0);
}
