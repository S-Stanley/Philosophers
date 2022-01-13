/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:01:24 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 22:02:15 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	exit_err_main(int *stop, pthread_mutex_t *commun_mutex, int mode)
{
	if (mode > 0)
		free(stop);
	free(commun_mutex);
	return (0);
}

void	exit_err_ft_philo(int *stop, void *forks, t_data *tmp, t_arg arg)
{
	if (stop)
		stop[0] = 1;
	destroy_mutex(forks, arg.nbr_philo);
	if (tmp)
		free_data(tmp);
	free(forks);
}

void	free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data->next;
		free(data->thread);
		free(data);
		data = tmp;
	}
}
