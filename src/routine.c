/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/11 21:14:16 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philo_is_thinking(struct timeval time, int to_think, char *name)
{
	long int	time_to_think;

	time_to_think = time.tv_sec + to_think;
	printf("%ld %s is thinking \n", time.tv_sec, name);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec >= time_to_think)
			break ;
	}
}

void	philo_is_sleeping(struct timeval time, int to_sleep, char *name)
{
	long int	time_to_sleep;

	time_to_sleep = time.tv_sec + to_sleep;
	printf("%ld %s is sleeping \n", time.tv_sec, name);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec >= time_to_sleep)
			break ;
	}
}

void	philo_is_eating(struct timeval time, int to_eat, char *name)
{
	long int	time_to_eat;

	time_to_eat = time.tv_sec + to_eat;
	printf("%ld %s is eating \n", time.tv_sec, name);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec >= time_to_eat)
			break ;
	}
}

void	*routine(void *arg)
{
	t_root			*root;
	struct timeval	time;
	long int		time_to_die;

	root = (t_root *)arg;
	// if (pthread_mutex_lock(root->g_mutex) != 0)
		// return (free_root_and_return(root));
	printf("creating philo %s with id %d\n", root->name, root->id);
	gettimeofday(&time, NULL);
	time_to_die = time.tv_sec + 5;
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec >= time_to_die)
			break ;
		gettimeofday(&time, NULL);
		philo_is_eating(time, 2, root->name);
		gettimeofday(&time, NULL);
		if (time.tv_sec >= time_to_die)
			break ;
		gettimeofday(&time, NULL);
		philo_is_sleeping(time, 2, root->name);
		gettimeofday(&time, NULL);
		if (time.tv_sec >= time_to_die)
			break ;
		gettimeofday(&time, NULL);
		philo_is_thinking(time, 2, root->name);
	}
	printf("%s just die\n", root->name);
	// if (pthread_mutex_unlock(root->g_mutex) != 0)
		// return (free_root_and_return(root));
	return (free_root_and_return(root));
}
