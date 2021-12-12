/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/12 13:53:03 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philo_is_thinking(struct timeval time, int to_think, char *name)
{
	long int	time_to_think;

	time_to_think = time.tv_usec + to_think;
	printf("%d %s is thinking \n", time.tv_usec, name);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_usec > time_to_think)
			break ;
	}
}

void	philo_is_sleeping(struct timeval time, int to_sleep, char *name)
{
	long int	time_to_sleep;

	time_to_sleep = time.tv_usec + to_sleep;
	printf("%d %s is sleeping \n", time.tv_usec, name);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_usec > time_to_sleep)
			break ;
	}
}

void	philo_is_eating(struct timeval time, int to_eat, t_root *root)
{
	long int	time_to_eat;

	time_to_eat = time.tv_usec + to_eat;
	printf("%d %s is eating \n", time.tv_usec, root->name);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_usec > time_to_eat)
			break ;
	}
}

typedef struct s_couvert {
	t_dishes	*left;
	t_dishes	*right;
}	t_couvert;

t_couvert	get_philo_fork(unsigned int id, t_dishes *fork)
{
	t_couvert	to_return;
	t_dishes	*tmp;
	int			copy_id;

	tmp = fork;
	copy_id = id;
	while (id > 0 && fork->next)
	{
		fork = fork->next;
		id--;
	}
	to_return.left = fork;
	if (fork->next)
	{
		fork = fork->next;
		to_return.right = fork;
	}
	else
		to_return.right = tmp;
	return (to_return);
}

void	*routine(void *arg)
{
	t_root			*root;
	struct timeval	time;
	long int		time_to_die;
	t_couvert		couvert;
	int				time_start;

	root = (t_root *)arg;
	couvert = get_philo_fork(root->id, root->fork);
	gettimeofday(&time, NULL);
	time_to_die = time.tv_usec + root->arg.t_die;
	while (1)
	{
		gettimeofday(&time, NULL);
		time_start = time.tv_usec;
		if (time.tv_usec > time_to_die)
			break ;
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&couvert.right->fork);
		pthread_mutex_lock(&couvert.left->fork);
		gettimeofday(&time, NULL);
		printf("%d %s has taken a fork\n", time.tv_usec, root->name);
		philo_is_eating(time, root->arg.t_eat, root);
		gettimeofday(&time, NULL);
		time_to_die = time.tv_usec + root->arg.t_die;
		if (time.tv_usec > time_to_die)
			break ;
		gettimeofday(&time, NULL);
		pthread_mutex_unlock(&couvert.right->fork);
		pthread_mutex_unlock(&couvert.left->fork);
		philo_is_sleeping(time, root->arg.t_sleep, root->name);
		gettimeofday(&time, NULL);
		if (time.tv_usec > time_to_die)
			break ;
		gettimeofday(&time, NULL);
		philo_is_thinking(time, 1, root->name);
	}
	printf("%d %s just died\n", time.tv_usec, root->name);
	return (free_root_and_return(root));
}

void	*routine2(void *arg)
{
	t_root			*root;
	struct timeval	time;
	long int		time_to_die;
	t_couvert		couvert;

	root = (t_root *)arg;
	couvert = get_philo_fork(root->id, root->fork);
	gettimeofday(&time, NULL);
	time_to_die = time.tv_usec + root->arg.t_die;
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_usec > time_to_die)
			break ;
		gettimeofday(&time, NULL);
		philo_is_thinking(time, 1, root->name);
		gettimeofday(&time, NULL);
		if (time.tv_usec > time_to_die)
			break ;
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&couvert.right->fork);
		pthread_mutex_lock(&couvert.left->fork);
		gettimeofday(&time, NULL);
		printf("%d %s has taken a fork\n", time.tv_usec, root->name);
		philo_is_eating(time, root->arg.t_eat, root);
		gettimeofday(&time, NULL);
		time_to_die = time.tv_usec + root->arg.t_die;
		if (time.tv_usec > time_to_die)
			break ;
		gettimeofday(&time, NULL);
		pthread_mutex_unlock(&couvert.right->fork);
		pthread_mutex_unlock(&couvert.left->fork);
		philo_is_sleeping(time, root->arg.t_sleep, root->name);
	}
	printf("%d %s just died\n", time.tv_usec, root->name);
	return (free_root_and_return(root));
}