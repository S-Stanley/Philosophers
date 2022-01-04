/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:58:50 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/04 01:47:11 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	eating(t_data *data, struct timeval start_time)
{
	printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
	printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
	printf("%ld philo %d is eating\n", get_time(data->time), data->id);
	ft_sleep(data->t_eat, data, start_time);
}

void	sleeping(t_data *data, struct timeval start_time)
{
	printf("%ld philo %d is sleeping\n", get_time(data->time), data->id);
	ft_sleep(data->t_sleep, data, start_time);
}

void	thinking(t_data *data)
{
	printf("%ld philo %d is thinking\n", get_time(data->time), data->id);
}

BOOL	ft_loop(t_data *data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	if (data->id % 2)
	{
		lock_fork(data);
		eating(data, start_time);
		unlock_fork(data);
		sleeping(data, start_time);
		thinking(data);
	}
	else
	{
		thinking(data);
		sleeping(data, start_time);
		lock_fork(data);
		eating(data, start_time);
		unlock_fork(data);
	}
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(start_time, data))
		return (FALSE);
	pthread_mutex_unlock(data->mutex);
	return (TRUE);
}

void	*routine(void *arg)
{
	t_data			*data;
	int				ate;

	ate = 0;
	data = (t_data *)arg;
	while (TRUE)
	{
		if (!ft_loop(data))
			break ;
		ate++;
		if (ate == data->max_t_eat)
			break ;
	}
	free(arg);
	return (NULL);
}
