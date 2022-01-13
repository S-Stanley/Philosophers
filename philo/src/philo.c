/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:06:03 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 22:06:24 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_data	*init_philo(pthread_mutex_t *forks, struct timeval prog_time_start,
						pthread_mutex_t *commun_mutex, t_arg arg)
{
	t_data			*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->forks = forks;
	data->prog_time_start = prog_time_start;
	data->t_eat = arg.t_eat;
	data->t_sleep = arg.t_sleep;
	data->t_die = arg.t_die;
	data->max_t_eat = arg.max_t_eat;
	data->nbr_philo = arg.nbr_philo;
	data->commun_mutex = commun_mutex;
	data->next = NULL;
	data->thread = malloc(sizeof(pthread_t));
	return (data);
}

t_data	*add_tmp(t_data *tmp, t_data *new)
{
	t_data	*buffer;

	if (!tmp)
		return (new);
	buffer = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (buffer);
}

void	join_philo(t_arg arg, t_data *tmp, void *forks, int *stop)
{
	int				i;
	t_data			*data_to_free;

	i = -1;
	data_to_free = tmp;
	while ((unsigned int)++i < arg.nbr_philo)
	{
		if (pthread_join(*tmp->thread, NULL) != 0)
		{
			stop[0] = 1;
			break ;
		}
		tmp = tmp->next;
	}
	free_data(data_to_free);
	destroy_mutex(forks, arg.nbr_philo);
	free(forks);
}

void	ft_philo(t_arg arg, int *stop, pthread_mutex_t *commun_mutex)
{
	int				i;
	struct timeval	prog_time_start;
	t_data			*data;
	t_data			*tmp;
	void			*forks;

	i = -1;
	forks = setup_fork(arg);
	if (!forks)
		return ;
	tmp = NULL;
	if (gettimeofday(&prog_time_start, NULL) == -1)
		return (exit_err_ft_philo(stop, forks, tmp, arg));
	while ((unsigned int)++i < arg.nbr_philo)
	{
		data = init_philo(forks, prog_time_start, commun_mutex, arg);
		if (!data)
			return (exit_err_ft_philo(stop, forks, tmp, arg));
		data->stop = stop;
		data->id = i + 1;
		tmp = add_tmp(tmp, data);
		if (pthread_create(data->thread, NULL, routine, data) != 0)
			return (exit_err_ft_philo(stop, forks, tmp, arg));
	}
	join_philo(arg, tmp, forks, stop);
}
