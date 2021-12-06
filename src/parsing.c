/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:06:07 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/06 20:09:15 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_arg	setup_arg(int argc, char **argv)
{
	t_arg	arg;

	arg.nbr_philo = atoi(argv[1]);
	arg.t_die = atoi(argv[2]);
	arg.t_eat = atoi(argv[3]);
	arg.t_sleep = atoi(argv[4]);
	if (argc == 6)
		arg.nbr_philo = atoi(argv[5]);
	return (arg);
}
