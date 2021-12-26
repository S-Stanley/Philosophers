/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:49:35 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:49:56 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	print_and_exit(char *message)
{
	write(1, "Error\n", ft_strlen("Error\n"));
	write(1, message, ft_strlen(message));
	return (1);
}

int	*get_stop_value(void)
{
	int	*stop;

	stop = malloc(sizeof(int));
	if (!stop)
		return (NULL);
	stop[0] = 0;
	return (stop);
}

long long int	*get_total_time(void)
{
	long long int	*total_time;

	total_time = malloc(sizeof(long long int));
	if (!total_time)
		return (NULL);
	total_time[0] = 0;
	return (total_time);
}
