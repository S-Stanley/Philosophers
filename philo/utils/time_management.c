/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:39:27 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:35:56 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

long int	get_timestamp(struct timeval tmp)
{
	struct timeval	now;
	long int		max_value_usec;
	long int		iter_time;

	max_value_usec = 999999;
	gettimeofday(&now, NULL);
	if (now.tv_sec == tmp.tv_sec)
		iter_time = now.tv_usec - tmp.tv_usec;
	else
		iter_time = now.tv_usec + (max_value_usec - tmp.tv_usec);
	iter_time = iter_time / ONE_MINI_SECOND;
	return (iter_time);
}
