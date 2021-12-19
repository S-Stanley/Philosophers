/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:08:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 21:07:29 by sserbin          ###   ########.fr       */
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

char	*free_root_and_return_null(t_root *root)
{
	free(root);
	return (NULL);
}

void	*free_root_and_return(t_root *root)
{
	free(root);
	return (NULL);
}
