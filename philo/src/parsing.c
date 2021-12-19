/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:06:07 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/19 19:07:24 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

BOOLEAN	check_error_arg(char **argv)
{
	unsigned int	i;
	unsigned int	x;

	i = 1;
	while (argv[i])
	{
		x = 0;
		while (argv[i][x])
		{
			if (argv[i][x] < '0' || argv[i][x] > '9')
			{
				printf("Unexpected charactere at position %d %d\n", i, x);
				return (TRUE);
			}
			x++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) == 0)
	{
		printf("The number of philo cannot be lower than 1\n");
		return (TRUE);
	}
	return (FALSE);
}

t_arg	setup_arg(int argc, char **argv)
{
	t_arg			arg;

	arg.nbr_philo = ft_atoi(argv[1]);
	arg.t_die = ft_atoi(argv[2]);
	arg.t_eat = ft_atoi(argv[3]);
	arg.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg.nbr_philo = ft_atoi(argv[5]);
	return (arg);
}
