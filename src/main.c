/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 23:15:24 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/09 20:32:18 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_arg			arg;
	t_philo			*philo;
	pthread_mutex_t	mutex;

	if (argc != 4 && argc != 5)
		print_and_exit("Wrong number or arguments");
	arg = setup_arg(argc, argv);
	philo = setup_philo(arg, &mutex);
	pthread_mutex_init(&mutex, NULL);
	create_thread_and_join_for_philo(philo);
	free_philo(philo);
	pthread_mutex_destroy(&mutex);
	return (0);
}
