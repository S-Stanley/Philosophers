/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:17:30 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:43:28 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

BOOLEAN	print_str(	int type, struct timeval tmp, t_root root,
					long long int *tt)
{
	if (root.stop[0])
		return (FALSE);
	if (!check_philo_alive(tmp, root))
		return (FALSE);
	*tt = *tt + (long long int)get_timestamp(tmp);
	if (type == 0)
		printf("%lld %d has taken a fork\n", *tt, root.id);
	if (type == 1)
		printf("%lld %d is eating\n", *tt, root.id);
	if (type == 2)
		printf("%lld %d is sleeping\n", *tt, root.id);
	if (type == 3)
		printf("%lld %d is thinking\n", *tt, root.id);
	if (!check_philo_alive(tmp, root))
		return (FALSE);
	return (TRUE);
}
