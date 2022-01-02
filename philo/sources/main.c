/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:52:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/02 23:08:18 by sserbin          ###   ########.fr       */
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
#define TIME_TO_DIE		411
#define NB_PHILO		2
#define BOOL			int

typedef struct s_data {
	int				id;
	pthread_mutex_t	*mutex;
	struct timeval	time;
}	t_data;

long int	*create_timestamp(void);
t_data		*create_data(int id, struct timeval time, pthread_mutex_t *mutex);
void		*routine(void *arg);
void		eating(t_data *data);
void		sleeping(t_data *data);
void		thinking(t_data *data);
long int	get_time(struct timeval time);

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
		eating(data);
		pthread_mutex_unlock(data->mutex);
		sleeping(data);
		thinking(data);
		pthread_mutex_lock(data->mutex);
		if (get_time(start_time) > TIME_TO_DIE)
		{
			printf("%ld philo %d died\n", get_time(start_time), data->id);
			pthread_mutex_unlock(data->mutex);
			exit(0);
		}
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

// BOOL	is_alive(t_data *data)
// {
// 	if ()
// }

void	eating(t_data *data)
{
	printf("%ld philo %d is eating\n", get_time(data->time), data->id);
	usleep(1000 * TIME_TO_EAT);
	printf("%ld philo %d dropped fork\n", get_time(data->time), data->id);
}

void	sleeping(t_data *data)
{
	printf("%ld philo %d is slepping\n", get_time(data->time), data->id);
	usleep(1000 * TIME_TO_SLEEP);
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
