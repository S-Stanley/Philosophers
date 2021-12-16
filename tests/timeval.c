/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 01:17:18 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/14 01:24:12 by sserbin          ###   ########.fr       */
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
	long long int	total;

	total = 0;
	while (TRUE)
	{
		gettimeofday(&time, NULL);
		printf("%d %lld \n", time.tv_usec, total);
		total = total + (long long int)time.tv_usec;
		usleep(100);
	}
}
