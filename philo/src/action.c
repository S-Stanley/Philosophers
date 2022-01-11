/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:58:50 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/11 23:45:16 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

BOOL	print_something(t_data *data, int content)
{
	pthread_mutex_lock(data->mutex);
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->mutex);
		return (FALSE);
	}
	if (content == 0)
		printf("%ld philo %d has taken a fork\n",
			get_time(data->time), data->id);
	if (content == 1)
		printf("%ld philo %d is eating\n", get_time(data->time), data->id);
	if (content == 2)
		printf("%ld philo %d is sleeping\n", get_time(data->time), data->id);
	if (content == 3)
		printf("%ld philo %d is thinking\n", get_time(data->time), data->id);
	pthread_mutex_unlock(data->mutex);
	return (TRUE);
}

BOOL	eating(t_data *data, struct timeval start_time)
{
	if (!print_something(data, 0))
		return (FALSE);
	if (!print_something(data, 0))
		return (FALSE);
	if (!print_something(data, 1))
		return (FALSE);
	if (!ft_sleep(data->t_eat, data, start_time))
		return (FALSE);
	return (TRUE);
}

BOOL	sleeping(t_data *data, struct timeval start_time)
{
	if (!print_something(data, 2))
		return (FALSE);
	if (!ft_sleep(data->t_sleep, data, start_time))
		return (FALSE);
	return (TRUE);
}

BOOL	thinking(t_data *data)
{
	if (!print_something(data, 3))
		return (FALSE);
	return (TRUE);
}

void	wait_a_little(t_data *data)
{
	if (count_len_philo(data->philo) % 2)
	{
		if (data->id % 3 == 2)
			usleep(data->t_eat * 1000);
		if (data->id % 3 == 0)
			usleep((data->t_eat + data->t_sleep - 100) * 1000);
	}
	else
	{
		if (data->id % 2 == 0)
			usleep(data->t_eat * 1000);
	}
}

BOOL	ft_loop(t_data *data, struct timeval *start_time)
{
	lock_fork(data);
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(*start_time, data))
	{
		unlock_fork(data);
		return (FALSE);
	}
	gettimeofday(start_time, NULL);
	pthread_mutex_unlock(data->mutex);
	if (!eating(data, *start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	unlock_fork(data);
	if (!sleeping(data, *start_time))
		return (FALSE);
	if (!thinking(data))
		return (FALSE);
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(*start_time, data))
		return (FALSE);
	pthread_mutex_unlock(data->mutex);
	// if (count_len_philo(data->philo) % 3 == 0)
	// 	usleep(data->t_eat * 1000);
	return (TRUE);
}
