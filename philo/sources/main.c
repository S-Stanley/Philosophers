/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:52:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/03 00:34:14 by sserbin          ###   ########.fr       */
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
#define TIME_TO_DIE		1000
#define NB_PHILO		2
#define BOOL			int
#define MAX_TIME_TO_EAT	2

typedef struct s_data {
	int				id;
	pthread_mutex_t	*mutex;
	struct timeval	time;
}	t_data;

long int	*create_timestamp(void);
t_data		*create_data(int id, struct timeval time, pthread_mutex_t *mutex);
void		*routine(void *arg);
void		eating(t_data *data, struct timeval start_time);
void		sleeping(t_data *data, struct timeval start_time);
void		thinking(t_data *data);
long int	get_time(struct timeval time);
void		check_philo_life(struct timeval start_time, t_data *data);
void		ft_sleep(long int sleepingtime, t_data *data, struct timeval start_time);

void	check_philo_life(struct timeval start_time, t_data *data)
{
	if (get_time(start_time) > TIME_TO_DIE)
	{
		printf("%ld philo %d died\n", get_time(start_time), data->id);
		pthread_mutex_unlock(data->mutex);
		exit(0);
	}
}

void	*routine(void *arg)
{
	t_data			*data;
	struct timeval	time;
	struct timeval	start_time;

	data = (t_data *)arg;
	while (TRUE)
	{
		gettimeofday(&start_time, NULL);
		pthread_mutex_lock(data->mutex);
		eating(data, start_time);
		pthread_mutex_unlock(data->mutex);
		sleeping(data, start_time);
		thinking(data);
		pthread_mutex_lock(data->mutex);
		check_philo_life(start_time, data);
		pthread_mutex_unlock(data->mutex);
	}
	free(arg);
}

long int	get_time(struct timeval time)
{
	struct timeval	now;
	long int		max;

	max = 999999;
	gettimeofday(&now, NULL);
	if (now.tv_sec == time.tv_sec)
		return ((now.tv_usec - time.tv_usec) / 1000);
	else
		return ((((max - time.tv_usec) + now.tv_usec) + ((now.tv_sec - time.tv_sec -1)*max)) / 1000);
}

void	ft_sleep(long int sleepingtime, t_data *data, struct timeval start_time)
{
	while (sleepingtime > 0)
	{
		check_philo_life(start_time, data);
		usleep(10 * 1000);
		sleepingtime = sleepingtime - 10;
	}
}

void	eating(t_data *data, struct timeval start_time)
{
	printf("%ld philo %d is eating\n", get_time(data->time), data->id);
	ft_sleep(TIME_TO_EAT, data, start_time);
	printf("%ld philo %d dropped fork\n", get_time(data->time), data->id);
}

void	sleeping(t_data *data, struct timeval start_time)
{
	printf("%ld philo %d is slepping\n", get_time(data->time), data->id);
	ft_sleep(TIME_TO_SLEEP, data, start_time);
}

void	thinking(t_data *data)
{
	printf("%ld philo %d is thinking\n", get_time(data->time), data->id);
}

t_data	*create_data(int id, struct timeval time, pthread_mutex_t *mutex)
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
	struct timeval	time;
	pthread_mutex_t	mutex;

	gettimeofday(&time, NULL);
	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < NB_PHILO)
		pthread_create(&threads[i], NULL, routine, create_data(i, time, &mutex));
	i = -1;
	while (++i < NB_PHILO)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}
