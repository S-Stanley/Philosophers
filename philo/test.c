/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:03:03 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/10 23:04:48 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	guess_grp(int nb)
{
	int	group;

	if (nb == 1 || nb == 2 || nb == 3)
		return (nb);
	group = 1;
	while (nb != 0)
	{
		if (group == 3)
			group = 1;
		else
			group++;
		nb--;
	}
	return (group);
}

int	main(int ac, char **av)
{
	printf("%d\n", guess_grp(atoi(av[1])));
	return (0);
}
