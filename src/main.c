/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:55:36 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 20:42:38 by sserbin          ###   ########.fr       */
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
	if (!philo)
		return (print_and_exit("Erreur malloc at setup_philo\n"));
	if (pthread_mutex_init(&g_mutex, NULL) != 0)
		return (print_and_exit("Error starting mutex\n"));
	if (!setup_philo_routine(&g_mutex, philo))
	{
		free_philo(philo);
		return (print_and_exit("Error while setting up routine"));
	}
	free_philo(philo);
	if (pthread_mutex_destroy(&g_mutex))
		return (print_and_exit("Error while destroying mutex\n"));
	return (0);
}
