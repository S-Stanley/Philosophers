/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:07:26 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 22:08:40 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

BOOL	eating(t_data *data, struct timeval *start_time)
{
	if (!lock_fork(data, start_time))
		return (FALSE);
	if (get_time(*start_time) > data->t_die)
	{
		if (pthread_mutex_lock(data->commun_mutex) != 0)
			return (FALSE);
		printf("%ld philo %u died\n", get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	if (!print_something(data, 1, start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	if (gettimeofday(start_time, NULL) == -1)
		return (FALSE);
	ft_sleep(data->t_eat, data, *start_time);
	unlock_fork(data);
	return (TRUE);
}

void	*routine(void *arg)
{
	t_data			*data;
	struct timeval	start_time;
	int				ate;

	data = (t_data *)arg;
	if (gettimeofday(&start_time, NULL) == -1)
		return (arg);
	if (data->id % 2)
		ft_sleep(data->t_eat, data, start_time);
	ate = 0;
	while (1)
	{
		if (!eating(data, &start_time))
			break ;
		ate++;
		if (data->max_t_eat > 0 && ate == data->max_t_eat)
			break ;
		if (!print_something(data, 2, &start_time))
			break ;
		ft_sleep(data->t_sleep, data, start_time);
		if (!print_something(data, 3, &start_time))
			break ;
	}
	return (arg);
}
