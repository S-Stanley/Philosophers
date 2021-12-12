/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/12 11:30:40 by sserbin          ###   ########.fr       */
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

void	philo_is_eating(struct timeval time, int to_eat, t_root *root)
{
	long int	time_to_eat;

	time_to_eat = time.tv_sec + to_eat;
	printf("%ld %s is eating \n", time.tv_sec, root->name);
	while (1)
	{
		gettimeofday(&time, NULL);
		if (time.tv_sec >= time_to_eat)
			break ;
	}
}

typedef struct s_couvert {
	t_dishes	*left;
	t_dishes	*right;
}	t_couvert;

t_couvert	get_philo_fork(unsigned int id, t_dishes *fork, char *name)
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
	printf("Philo %s with id %d ; left fork %d ; right fork %d\n", name, copy_id, to_return.left->id, to_return.right->id);
	return (to_return);
}

void	*routine(void *arg)
{
	t_root			*root;
	// struct timeval	time;
	// long int		time_to_die;

	root = (t_root *)arg;
	get_philo_fork(root->id, root->fork, root->name);
	// printf("creating philo %s with id %d\n", root->name, root->id);
	// gettimeofday(&time, NULL);
	// time_to_die = time.tv_sec + 5;
	// while (1)
	// {
	// 	gettimeofday(&time, NULL);
	// 	if (time.tv_sec >= time_to_die)
	// 		break ;
	// 	gettimeofday(&time, NULL);
	// 	philo_is_eating(time, 2, root);
	// 	gettimeofday(&time, NULL);
	// 	if (time.tv_sec >= time_to_die)
	// 		break ;
	// 	gettimeofday(&time, NULL);
	// 	philo_is_sleeping(time, 2, root->name);
	// 	gettimeofday(&time, NULL);
	// 	if (time.tv_sec >= time_to_die)
	// 		break ;
	// 	gettimeofday(&time, NULL);
	// 	philo_is_thinking(time, 2, root->name);
	// }
	// printf("%s just die\n", root->name);
	return (free_root_and_return(root));
}
