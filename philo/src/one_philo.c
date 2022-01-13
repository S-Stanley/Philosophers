/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:14:56 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 18:20:17 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	one_philo(t_arg arg, int *stop, pthread_mutex_t *commun_mutex)
{
	struct timeval	start_time;
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return ;
	gettimeofday(&start_time, NULL);
	data->t_die = arg.t_die;
	data->commun_mutex = commun_mutex;
	data->prog_time_start = start_time;
	data->stop = stop;
	data->id = 1;
	printf("%ld philo %d as taken a fork\n", get_time(start_time), data->id);
	ft_sleep(data->t_die + 1, data, start_time);
	free(data);
}
