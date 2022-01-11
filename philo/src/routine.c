/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:01:11 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/11 20:34:16 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	one_philo(t_data *data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	printf("%ld philo %d as taken a fork\n", get_time(start_time), data->id);
	ft_sleep(data->t_die + 1, data, start_time);
}

int	count_len_philo(t_philo *philo)
{
	int	count;

	if (!philo)
		return (0);
	count = 0;
	while (philo)
	{
		count++;
		philo = philo->next;
	}
	return (count);
}

void	*routine(void *arg)
{
	t_data			*data;
	int				ate;
	int				i;

	ate = 0;
	data = (t_data *)arg;
	i = 0;
	data->ate = 0;
	if (count_len_philo(data->philo) == 1)
	{
		one_philo(data);
		free(data);
		return (NULL);
	}
	while (TRUE)
	{
		if (!ft_loop1(data))
			break ;
		ate++;
		if (ate == data->max_t_eat)
			break ;
		i++;
	}
	free(data);
	return (NULL);
}
