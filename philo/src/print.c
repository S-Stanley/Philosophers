/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:03:08 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 22:03:20 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_content(t_data *data, int content)
{
	if (content == 0)
		printf("%ld philo %u has taken a fork\n",
			get_time(data->prog_time_start), data->id);
	if (content == 1)
		printf("%ld philo %u is eating\n",
			get_time(data->prog_time_start), data->id);
	if (content == 2)
		printf("%ld philo %u is sleeping\n",
			get_time(data->prog_time_start), data->id);
	if (content == 3)
		printf("%ld philo %u is thinking\n",
			get_time(data->prog_time_start), data->id);
}

BOOL	print_something(t_data *data, int content, struct timeval *start_time)
{
	if (pthread_mutex_lock(data->commun_mutex) != 0)
		return (FALSE);
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	if (get_time(*start_time) > data->t_die)
	{
		data->stop[0] = 1;
		printf("%ld philo %u died\n", get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	print_content(data, content);
	if (pthread_mutex_unlock(data->commun_mutex) != 0)
		return (FALSE);
	return (TRUE);
}
