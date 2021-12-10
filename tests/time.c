/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:16:40 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 21:32:07 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld\n", time.tv_sec);
}
