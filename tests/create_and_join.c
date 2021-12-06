/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 23:13:12 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/06 01:58:50 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int	g_mails = 0;

void	*my_turn(void *arg)
{
	unsigned int	i;

	i = 0;
	while (i < 5)
	{
		sleep(1);
		g_mails++;
		printf("My turn %u\n", i);
		i++;
	}
}

void	your_turn(void)
{
	unsigned int	i;

	i = 0;
	while (i < 3)
	{
		sleep(1);
		g_mails++;
		printf("Your turn %u\n", i);
		i++;
	}
}

int	main(void)
{
	pthread_t	thd;

	if (pthread_create(&thd, NULL, my_turn, NULL) != 0)
		return (1);
	if (pthread_join(thd, NULL) != 0)
		return (1);
	your_turn();
}
