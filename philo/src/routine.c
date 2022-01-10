/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:01:11 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/10 23:25:16 by sserbin          ###   ########.fr       */
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
	data->ate = 0;
	while (TRUE)
	{
		if (data->id % 3 == 2)
		{
			if (!ft_loop1(data))
				break ;
		}
		else if (data->id % 3 == 1)
		{
			if (!ft_loop2(data))
				break ;
		}
		else
		{
			usleep(data->t_eat * 1000);
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
