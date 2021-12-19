/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:17:18 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/19 15:50:58 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define TRUE 1

int	main(void)
{
	struct timeval	time;
	struct timeval	buffer;

	gettimeofday(&buffer, NULL);
	while (TRUE)
	{
		gettimeofday(&time, NULL);
		if (time.tv_usec > buffer.tv_usec)
		{
			printf("%ld %ld\n", time.tv_sec, time.tv_usec);
			buffer = time;
		}
	}
}
