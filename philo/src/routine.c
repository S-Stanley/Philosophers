/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 02:01:11 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/06 19:32:53 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*routine(void *arg)
{
	t_data			*data;
	int				ate;

	ate = 0;
	data = (t_data *)arg;
	while (TRUE)
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
	}
	free(data->stop);
	free(data);
	return (NULL);
}
