/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/15 01:02:39 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philo_is_thinking(int to_think, char *name, long long int timestamp_now, long long int timestamp_max)
{
	(void)to_think;
	printf("%lld %s is thinking \n", timestamp_max - timestamp_now, name);
}

void	philo_is_sleeping(int to_sleep, char *name, long long int timestamp_now, long long int timestamp_max)
{
	printf("%lld %s is sleeping \n", timestamp_max - timestamp_now, name);
	usleep(to_sleep);
}

void	philo_is_eating(int to_eat, t_root *root, long long int timestamp_now, long long int timestamp_max)
{
	printf("%lld %s is eating \n", timestamp_max - timestamp_now, root->name);
	usleep(to_eat);
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
	t_couvert		couvert;
	long long int	timestamp_now;
	long long int	timestamp_max;

	root = (t_root *)arg;
	couvert = get_philo_fork(root->id, root->fork);
	gettimeofday(&time, NULL);
	timestamp_now = 0;
	timestamp_now = timestamp_now + (long long int)time.tv_usec;
	timestamp_max = timestamp_now + (long long int)root->arg.t_die;
	while (1)
	{
		if (pthread_mutex_lock(&couvert.right->fork) != 0)
			printf("ERROR MUTEX LOCK 0\n");
		if (pthread_mutex_lock(&couvert.left->fork) != 0)
			printf("ERROR MUTEX LOCK 1\n");
		gettimeofday(&time, NULL);
		printf("%lld %s has taken a fork\n",
			timestamp_max - timestamp_now, root->name);
		gettimeofday(&time, NULL);
		timestamp_now = timestamp_now + (long long int)time.tv_usec;
		timestamp_max = timestamp_now + (long long int)root->arg.t_die;
		philo_is_eating(root->arg.t_eat, root, timestamp_now, timestamp_max);
		printf("%lld %s is going to dropm fork\n",
			timestamp_max - timestamp_now, root->name);
		if (pthread_mutex_unlock(&couvert.right->fork) != 0)
			printf("ERROR MUTEX UNLOCK 0\n");
		if (pthread_mutex_unlock(&couvert.left->fork) != 0)
			printf("ERROR MUTEX UNLOCK 1\n");
		printf("%lld %s just dropped fork\n",
			timestamp_max - timestamp_now, root->name);
		gettimeofday(&time, NULL);
		timestamp_now = timestamp_now + (long long int)time.tv_usec;
		philo_is_sleeping(root->arg.t_sleep, root->name,
			timestamp_now, timestamp_max);
		gettimeofday(&time, NULL);
		timestamp_now = timestamp_now + (long long int)time.tv_usec;
		philo_is_thinking(1, root->name, timestamp_now, timestamp_max);
		gettimeofday(&time, NULL);
		timestamp_now = timestamp_now + (long long int)time.tv_usec;
		usleep(200000);
	}
	printf("%lld %s just died\n", timestamp_max - timestamp_now, root->name);
	return (free_root_and_return(root));
}

/*
void	*routine(void *arg)
{
	t_root			*root;
	struct timeval	time;
	long int		time_to_die;
	t_couvert		couvert;
	int				time_start;
	long long int	total;

	root = (t_root *)arg;
	couvert = get_philo_fork(root->id, root->fork);
	total = 0;
	gettimeofday(&time, NULL);
	total = total + time.tv_usec;
	time_to_die = time.tv_usec + root->arg.t_die;
	while (1)
	{
		gettimeofday(&time, NULL);
		total = total + (long long int)time.tv_usec;
		time_start = total;
		// if (time.tv_usec > time_to_die)
		// 	break ;
		gettimeofday(&time, NULL);
		if (pthread_mutex_lock(&couvert.right->fork) != 0)
			printf("ERROR MUTEX LOCK 0\n");
		if (pthread_mutex_lock(&couvert.left->fork) != 0)
			printf("ERROR MUTEX LOCK 1\n");
		gettimeofday(&time, NULL);
		printf("%lld %s has taken a fork\n", time_to_die - total, root->name);
		philo_is_eating(time, root->arg.t_eat, root, time_to_die);
		printf("%s is going to dropm fork\n", root->name);
		if (pthread_mutex_unlock(&couvert.right->fork) != 0)
			printf("ERROR MUTEX UNLOCK 0\n");
		if (pthread_mutex_unlock(&couvert.left->fork) != 0)
			printf("ERROR MUTEX UNLOCK 1\n");
		printf("%lld %s just dropped fork\n",  time_to_die - total, root->name);
		time_to_die = total + root->arg.t_die;
		// if (time.tv_usec > time_to_die)
			// break ;
		// gettimeofday(&time, NULL);
		philo_is_sleeping(time, root->arg.t_sleep, root->name, time_to_die);
		// gettimeofday(&time, NULL);
		// if (time.tv_usec > time_to_die)
		// 	break ;
		// gettimeofday(&time, NULL);
		philo_is_thinking(time, 1, root->name, time_to_die);
		// usleep(10);
	}
	printf("%ld %s just died\n", time_to_die - time.tv_usec, root->name);
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
		philo_is_sleeping(time, root->arg.t_sleep, root->name);
		gettimeofday(&time, NULL);
		philo_is_thinking(time, 1, root->name);
		usleep(10);
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
	}
	printf("%d %s just died\n", time.tv_usec, root->name);
	return (free_root_and_return(root));
}
*/
