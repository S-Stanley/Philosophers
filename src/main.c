/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 23:15:24 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 14:12:10 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	g_global = 0;

int	main(int argc, char **argv)
{
	t_arg			arg;
	t_prog			prog;
	pthread_mutex_t	mutex;

	if (argc != 4 && argc != 5)
		print_and_exit("Wrong number or arguments");
	arg = setup_arg(argc, argv);
	prog.philo = setup_philo(arg);
	// g_global = 0;
	pthread_mutex_init(&g_mutex, NULL);
	create_thread_and_join_for_philo(prog, &mutex);
	pthread_mutex_destroy(&g_mutex);
	return (0);
}

/*
	free_philo(prog.philo);
	free(prog.mutex);
*/