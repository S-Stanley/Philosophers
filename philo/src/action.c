/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:58:50 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/11 20:16:02 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_philo	*set_philo_ate(t_philo *philo, unsigned int id, long int time)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		if (philo->id == id)
		{
			philo->ate++;
			(void)time;
			break ;
		}
		philo = philo->next;
	}
	return (tmp);
}

BOOL	print_something(t_data *data, int content)
{
	pthread_mutex_lock(data->mutex);
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->mutex);
		return (FALSE);
	}
	if (content == 0)
		printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
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
	pthread_mutex_lock(data->mutex);
	data->philo = set_philo_ate(data->philo, data->id, get_time(data->time));
	pthread_mutex_unlock(data->mutex);
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

BOOL	ft_loop1(t_data *data)
{
	struct timeval	start_time;

	if (data->id % 3 == 2)
		usleep(200 * 1000);
	if (data->id % 3 == 0)
		usleep(400 * 1000);
	gettimeofday(&start_time, NULL);
	lock_fork(data);
	if (!eating(data, start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	unlock_fork(data);
	if (!sleeping(data, start_time))
		return (FALSE);
	if (!thinking(data))
		return (FALSE);
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(start_time, data))
		return (FALSE);
	pthread_mutex_unlock(data->mutex);
	// usleep(200 * 1000);
	return (TRUE);
}