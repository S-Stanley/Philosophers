/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:52:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/06 19:56:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

BOOL	check_philo_life(struct timeval start_time, t_data *data)
{
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->mutex);
		return (FALSE);
	}
	if (get_time(start_time) > data->t_die)
	{
		if (data->stop[0])
			return (FALSE);
		printf("%ld philo %d died\n", get_time(data->time), data->id);
		data->stop[0] = 1;
		pthread_mutex_unlock(data->mutex);
		return (FALSE);
	}
	return (TRUE);
}

t_data	*create_data(int id, pthread_mutex_t *mutex, t_arg arg, int *stop)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->id = id;
	data->mutex = mutex;
	data->t_sleep = arg.t_sleep;
	data->t_eat = arg.t_eat;
	data->t_die = arg.t_die;
	data->max_t_eat = arg.max_t_eat;
	data->stop = stop;
	return (data);
}

void	join_philo(t_philo *philo, pthread_mutex_t mutex, int *stop)
{
	while (philo)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			return ;
		philo = philo->next;
	}
	free(stop);
	pthread_mutex_destroy(&mutex);
}

void	start_program(t_arg arg, t_philo *philo, t_dishes *fork)
{
	t_philo			*tmp;
	struct timeval	time;
	pthread_mutex_t	mutex;
	t_data			*data;
	int				*stop;

	gettimeofday(&time, NULL);
	tmp = philo;
	pthread_mutex_init(&mutex, NULL);
	stop = create_stop_var();
	while (philo)
	{
		data = create_data(philo->id, &mutex, arg, stop);
		if (!data)
			return ;
		data->time = time;
		data->fork = fork;
		if (pthread_create(&philo->thread, NULL, routine, data) != 0)
			return ;
		philo = philo->next;
	}
	join_philo(tmp, mutex, stop);
}

int	main(int argc, char **argv)
{
	t_arg			arg;
	t_philo			*philo;
	t_dishes		*fork;

	if (check_error_arg(argc, argv))
		return (0);
	arg = setup_arg(argc, argv);
	philo = setup_philo(arg);
	if (!philo)
		return (0);
	fork = init_mutex(arg.nbr_philo);
	if (!fork)
	{
		free_for_exit(fork, philo);
		return (0);
	}
	start_program(arg, philo, fork);
	free_for_exit(fork, philo);
	return (0);
}
