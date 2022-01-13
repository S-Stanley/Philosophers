/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:04:28 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 22:28:49 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

BOOL	lock_fork_last(t_data *data, struct timeval *start_time)
{
	if (pthread_mutex_lock(&data->forks[data->id - 1]) != 0)
		return (FALSE);
	if (!print_something(data, 0, start_time))
	{
		pthread_mutex_unlock(&data->forks[data->id - 1]);
		return (FALSE);
	}
	if (pthread_mutex_lock(&data->forks[0]) != 0)
	{
		pthread_mutex_unlock(&data->forks[data->id - 1]);
		return (FALSE);
	}
	if (!print_something(data, 0, start_time))
	{
		pthread_mutex_unlock(&data->forks[data->id - 1]);
		pthread_mutex_unlock(&data->forks[data->id]);
		return (FALSE);
	}
	return (TRUE);
}

BOOL	lock_fork_first(t_data *data, struct timeval *start_time)
{
	if (pthread_mutex_lock(&data->forks[data->id]) != 0)
		return (FALSE);
	if (!print_something(data, 0, start_time))
	{
		pthread_mutex_unlock(&data->forks[data->id]);
		return (FALSE);
	}
	if (pthread_mutex_lock(&data->forks[0]) != 0)
	{
		pthread_mutex_unlock(&data->forks[data->id]);
		return (FALSE);
	}
	if (!print_something(data, 0, start_time))
	{
		pthread_mutex_unlock(&data->forks[data->id]);
		pthread_mutex_unlock(&data->forks[data->nbr_philo]);
		return (FALSE);
	}
	return (TRUE);
}

BOOL	lock_fork_middle(t_data *data, struct timeval *start_time)
{
	if (pthread_mutex_lock(&data->forks[data->id - 1]) != 0)
		return (FALSE);
	if (!print_something(data, 0, start_time))
	{
		pthread_mutex_unlock(&data->forks[data->id - 1]);
		return (FALSE);
	}
	if (pthread_mutex_lock(&data->forks[data->id]) != 0)
	{
		pthread_mutex_unlock(&data->forks[data->id - 1]);
		return (FALSE);
	}
	if (!print_something(data, 0, start_time))
	{
		pthread_mutex_unlock(&data->forks[data->id - 1]);
		pthread_mutex_unlock(&data->forks[data->id]);
		return (FALSE);
	}
	return (TRUE);
}

BOOL	lock_fork(t_data *data, struct timeval *start_time)
{
	if (data->id == data->nbr_philo)
	{
		if (!lock_fork_last(data, start_time))
			return (FALSE);
	}
	else if (data->id == 1)
	{
		if (!lock_fork_first(data, start_time))
			return (FALSE);
	}
	else
	{
		if (!lock_fork_middle(data, start_time))
			return (FALSE);
	}
	return (TRUE);
}

void	*setup_fork(t_arg arg)
{
	void			*forks;

	forks = malloc(sizeof(pthread_mutex_t) * arg.nbr_philo);
	if (!forks)
		return (NULL);
	if (!init_mutex(forks, arg.nbr_philo))
	{
		free(forks);
		return (NULL);
	}
	return (forks);
}
