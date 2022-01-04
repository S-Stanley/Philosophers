/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:52:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/04 01:40:01 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_philo_life(struct timeval start_time, t_data *data)
{
	if (get_time(start_time) > data->t_die)
	{
		printf("%ld philo %d died\n", get_time(start_time), data->id);
		pthread_mutex_unlock(data->mutex);
		exit(0);
	}
}

t_data	*create_data(int id, pthread_mutex_t *mutex, t_arg arg, t_dishes *fork)
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
	data->fork = fork;
	return (data);
}

void	start_program(t_arg arg, t_philo *philo, t_dishes *fork)
{
	t_philo			*tmp;
	struct timeval	time;
	pthread_mutex_t	mutex;
	t_data			*data;

	gettimeofday(&time, NULL);
	tmp = philo;
	while (philo)
	{
		data = create_data(philo->id, &mutex, arg, fork);
		if (!data)
			return ;
		data->time = time;
		if (pthread_create(&philo->thread, NULL, routine, data) != 0)
			return ;
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			return ;
		philo = philo->next;
	}
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
