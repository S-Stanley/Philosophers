/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:01:11 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/09 19:40:18 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	int				size;
	int				i;

	ate = 0;
	data = (t_data *)arg;
	i = 0;
	size = count_len_philo(data->philo);
	while (i < size)
	{
		if (data->id % 2)
		{
			if (!ft_loop1(data))
				break ;
		}
		else
		{
			if (!ft_loop2(data))
				break ;
		}
		ate++;
		if (ate == data->max_t_eat)
			break ;
		i++;
	}
	free(data);
	return (NULL);
}
