/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:58:50 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/08 17:39:13 by sserbin          ###   ########.fr       */
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
			printf("%ld philo %u is eating for the %d time\n", time, id, philo->ate);
			break ;
		}
		philo = philo->next;
	}
	return (tmp);
}

BOOL	eating(t_data *data, struct timeval start_time)
{
	if (data->stop[0])
		return (FALSE);
	printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
	printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
	printf("%ld philo %d is eating\n", get_time(data->time), data->id);
	data->philo = set_philo_ate(data->philo, data->id, get_time(data->time));
	if (!ft_sleep(data->t_eat, data, start_time))
		return (FALSE);
	return (TRUE);
}

BOOL	sleeping(t_data *data, struct timeval start_time)
{
	if (data->stop[0])
		return (FALSE);
	printf("%ld philo %d is sleeping\n", get_time(data->time), data->id);
	if (!ft_sleep(data->t_sleep, data, start_time))
		return (FALSE);
	return (TRUE);
}

void	thinking(t_data *data)
{
	if (data->stop[0])
		return ;
	printf("%ld philo %d is thinking\n", get_time(data->time), data->id);
}

BOOL	smallest_eat(t_philo *philo, unsigned int id)
{
	int		mine;
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		if (philo->id == id)
			mine = philo->ate;
		philo = philo->next;
	}
	while (tmp)
	{
		if (tmp->id != id)
		{
			if (mine > tmp->ate)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

BOOL	ft_loop1(t_data *data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (!smallest_eat(data->philo, data->id))
		usleep(1);
	lock_fork(data);
	if (!eating(data, start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	unlock_fork(data);
	if (!sleeping(data, start_time))
		return (FALSE);
	thinking(data);
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(start_time, data))
		return (FALSE);
	pthread_mutex_unlock(data->mutex);
	return (TRUE);
}

BOOL	ft_loop2(t_data *data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	thinking(data);
	if (!sleeping(data, start_time))
		return (FALSE);
	while (!smallest_eat(data->philo, data->id))
		usleep(1);
	lock_fork(data);
	if (!eating(data, start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	unlock_fork(data);
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(start_time, data))
		return (FALSE);
	pthread_mutex_unlock(data->mutex);
	return (TRUE);
}
