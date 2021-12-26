/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 16:17:30 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:06:36 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

BOOLEAN	print_str(int type, struct timeval tmp, t_root root)
{
	if (root.stop[0])
		return (FALSE);
	if (!check_philo_alive(tmp, root))
		return (FALSE);
	if (type == 0)
		printf("%ld %d has taken a fork\n", get_timestamp(tmp), root.id);
	if (type == 1)
		printf("%ld %d is eating\n", get_timestamp(tmp), root.id);
	if (type == 2)
		printf("%ld %d is sleeping\n", get_timestamp(tmp), root.id);
	if (type == 3)
		printf("%ld %d is thinking\n", get_timestamp(tmp), root.id);
	if (!check_philo_alive(tmp, root))
		return (FALSE);
	return (TRUE);
}
