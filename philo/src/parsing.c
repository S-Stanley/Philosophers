/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:03:52 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/11 21:07:59 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

BOOL	print_and_return(void)
{
	printf("Wrong number or arguments\n");
	return (TRUE);
}

BOOL	is_arg_correct(char **argv, t_arg arg, int argc)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 0)
			return (FALSE);
		i++;
	}
	if (arg.nbr_philo > 200)
		return (FALSE);
	if (arg.t_die < 60)
		return (FALSE);
	if (arg.max_t_eat <= 0 && argc == 6)
		return (FALSE);
	if (arg.nbr_philo <= 0 || arg.t_die <= 0
		|| arg.t_eat <= 0 || arg.t_sleep <= 0)
		return (FALSE);
	return (TRUE);
}

BOOL	check_error_arg(int argc, char **argv)
{
	unsigned int	i;
	unsigned int	x;

	if (argc != 5 && argc != 6)
		return (print_and_return());
	i = 0;
	while (argv[++i])
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
		arg.max_t_eat = ft_atoi(argv[5]);
	else
		arg.max_t_eat = -1;
	return (arg);
}
