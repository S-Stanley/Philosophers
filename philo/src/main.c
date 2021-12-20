/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:55:36 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/20 01:23:10 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_dishes	*add_fork(t_dishes *fork, unsigned int i)
{
	t_dishes	*new;
	t_dishes	*tmp;

	new = malloc(sizeof(t_dishes));
	new->id = i;
	new ->next = NULL;
	if (!fork)
		return (new);
	tmp = fork;
	while (fork->next)
		fork = fork->next;
	fork->next = new;
	return (tmp);
}

t_dishes	*init_mutex(int nb)
{
	int			i;
	t_dishes	*fork;
	t_dishes	*tmp;

	fork = NULL;
	i = 0;
	while (i < nb)
	{
		fork = add_fork(fork, i);
		i++;
	}
	tmp = fork;
	while (fork)
	{
		pthread_mutex_init(&fork->fork, NULL);
		fork = fork->next;
	}
	return (tmp);
}

void	destroy_mutex(t_dishes *fork)
{
	t_dishes	*tmp;

	while (fork)
	{
		tmp = fork->next;
		pthread_mutex_destroy(&fork->fork);
		free(fork);
		fork = tmp;
	}
}

int	one_philo(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%d 1 as taking a fork\n", time.tv_usec);
	gettimeofday(&time, NULL);
	printf("%d 1 die\n", time.tv_usec);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	g_mutex;
	t_arg			arg;
	t_philo			*philo;
	t_dishes		*fork;

	if (check_error_arg(argc, argv))
		return (0);
	arg = setup_arg(argc, argv);
	if (arg.nbr_philo == 1)
		return (one_philo());
	philo = setup_philo(arg);
	fork = init_mutex(arg.nbr_philo);
	if (!philo)
		return (print_and_exit("Erreur malloc at setup_philo\n"));
	if (pthread_mutex_init(&g_mutex, NULL) != 0)
		return (print_and_exit("Error starting mutex\n"));
	if (!setup_philo_routine(&g_mutex, philo, fork, arg))
	{
		free_philo(philo);
		return (print_and_exit("Error while setting up routine"));
	}
	free_philo(philo);
	destroy_mutex(fork);
	return (0);
}
