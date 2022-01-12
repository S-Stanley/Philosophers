/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:59:27 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/09 18:46:09 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	*create_stop_var(void)
{
	int	*stop;

	stop = malloc(sizeof(int));
	if (!stop)
		return (NULL);
	stop[0] = 0;
	return (stop);
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
		return ((
				((max - time.tv_usec) + now.tv_usec)
				+ ((now.tv_sec - time.tv_sec -1) * max)) / 1000);
}

BOOL	ft_sleep(long int sleepingtime, t_data *data, struct timeval start_time)
{
	int		timeleft;

	timeleft = data->t_die - get_time(start_time);
	if (timeleft > sleepingtime)
		usleep(sleepingtime * 1000);
	else
	{
		while (sleepingtime > 0)
		{
			pthread_mutex_lock(data->mutex);
			if (!check_philo_life(start_time, data))
				return (FALSE);
			pthread_mutex_unlock(data->mutex);
			usleep(10 * 1000);
			sleepingtime = sleepingtime - 10;
		}
	}
	return (TRUE);
}

long int	*create_timestamp(void)
{
	long int	*time;

	time = malloc(sizeof(long int));
	if (!time)
		return (NULL);
	time[0] = 0;
	return (time);
}