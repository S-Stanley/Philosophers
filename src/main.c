/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:55:36 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 20:27:16 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	g_mutex;
	t_arg			arg;
	t_philo			*philo;

	if (argc != 4 && argc != 5)
		print_and_exit("Wrong number or arguments\n");
	arg = setup_arg(argc, argv);
	philo = setup_philo(arg);
	pthread_mutex_init(&g_mutex, NULL);
	setup_philo_routine(&g_mutex, philo);
	pthread_mutex_destroy(&g_mutex);
	free_philo(philo);
	philo = malloc(5);
	return (0);
}
