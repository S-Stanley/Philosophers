/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:08:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 19:08:17 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
}
