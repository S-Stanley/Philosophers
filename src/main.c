/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 23:15:24 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/08 21:58:02 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*philo;

	if (argc != 4 && argc != 5)
		print_and_exit("Wrong number or arguments");
	arg = setup_arg(argc, argv);
	philo = setup_philo(arg);
	free_philo(philo);
	return (0);
}
