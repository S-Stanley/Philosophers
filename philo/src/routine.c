/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/19 18:28:42 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct s_couvert {
	t_dishes	*left;
	t_dishes	*right;
}	t_couvert;

#define ONE_MINI_SECOND	1000
#define EATING			0
#define SLEEPING		1
#define THINKING		2

#define FALSE			0
#define TRUE			1
#define BOOLEAN			unsigned int

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

long int	get_timestamp(struct timeval tmp)
{
	struct timeval	now;
	long int		max_value_usec;
	long int		iter_time;

	max_value_usec = 999999;
	gettimeofday(&now, NULL);
	if (now.tv_sec == tmp.tv_sec)
		iter_time = now.tv_usec - tmp.tv_usec;
	else
		iter_time = now.tv_usec + (max_value_usec - tmp.tv_usec);
	iter_time = iter_time / ONE_MINI_SECOND;
	return (iter_time);
}

BOOLEAN	check_philo_alive(struct timeval tmp, t_root root)
{
	long int	iter_time;

	iter_time = get_timestamp(tmp);
	if (iter_time > root.arg.t_die)
	{
		printf("%ld %d died\n", get_timestamp(tmp), root.id);
		root.stop[0] = 1;
		return (FALSE);
	}
	if (root.stop[0])
		return (FALSE);
	return (TRUE);
}

BOOLEAN	action(int action, t_root root, struct timeval tmp)
{
	t_couvert		couvert;

	couvert = get_philo_fork(root.id, root.fork);
	if (!check_philo_alive(tmp, root))
		return (FALSE);
	if (action == EATING)
	{
		pthread_mutex_lock(&couvert.left->fork);
		pthread_mutex_lock(&couvert.right->fork);
		printf("%ld %d has taken a fork\n", get_timestamp(tmp), root.id);
		printf("%ld %d is eating\n", get_timestamp(tmp), root.id);
		usleep(root.arg.t_eat * ONE_MINI_SECOND);
		pthread_mutex_unlock(&couvert.left->fork);
		pthread_mutex_unlock(&couvert.right->fork);
	}
	else if (action == SLEEPING)
	{
		printf("%ld %d is sleeping\n", get_timestamp(tmp), root.id);
		// pthread_mutex_unlock(&couvert.left->fork);
		// pthread_mutex_unlock(&couvert.right->fork);
		usleep(root.arg.t_sleep * ONE_MINI_SECOND);
	}
	else
	{
		printf("%ld %d is thinking\n", get_timestamp(tmp), root.id);
	}
	return (TRUE);
}

BOOLEAN	what_to_do(int thread_nb, t_root root, struct timeval tmp)
{
	if ((thread_nb % 2) == 0)
	{
		if (!action(EATING, root, tmp))
			return (FALSE);
		if (!action(SLEEPING, root, tmp))
			return (FALSE);
		if (!action(THINKING, root, tmp))
			return (FALSE);
	}
	else
	{
		if (!action(SLEEPING, root, tmp))
			return (FALSE);
		if (!action(THINKING, root, tmp))
			return (FALSE);
		if (!action(EATING, root, tmp))
			return (FALSE);
	}
	return (TRUE);
}

void	*routine(void *arg)
{
	struct timeval	time;
	struct timeval	tmp;
	t_root			*root;

	root = (t_root *)arg;
	while (TRUE)
	{
		gettimeofday(&time, NULL);
		tmp = time;
		if (!what_to_do(root->id, *root, tmp))
			return (arg);
		if (!check_philo_alive(tmp, *root))
			return (arg);
	}
	return (arg);
}

// void	*ex_routine(void *arg)
// {
// 	t_root			*root;
// 	struct timeval	time;
// 	t_couvert		couvert;
// 	long long int	timestamp_now;
// 	long long int	timestamp_max;

// 	root = (t_root *)arg;
// 	couvert = get_philo_fork(root->id, root->fork);
// 	gettimeofday(&time, NULL);
// 	timestamp_now = 0;
// 	timestamp_now = timestamp_now + (long long int)time.tv_usec;
// 	timestamp_max = timestamp_now + (long long int)root->arg.t_die;
// 	while (1)
// 	{
// 		if (pthread_mutex_lock(&couvert.right->fork) != 0)
// 			printf("ERROR MUTEX LOCK 0\n");
// 		if (pthread_mutex_lock(&couvert.left->fork) != 0)
// 			printf("ERROR MUTEX LOCK 1\n");
// 		gettimeofday(&time, NULL);
// 		printf("%lld %s has taken a fork\n",
// 			timestamp_max - timestamp_now, root->name);
// 		gettimeofday(&time, NULL);
// 		timestamp_now = timestamp_now + (long long int)time.tv_usec;
// 		timestamp_max = timestamp_now + (long long int)root->arg.t_die;
// 		philo_is_eating(root->arg.t_eat, root, timestamp_now, timestamp_max);
// 		printf("%lld %s is going to dropm fork\n",
// 			timestamp_max - timestamp_now, root->name);
// 		if (pthread_mutex_unlock(&couvert.right->fork) != 0)
// 			printf("ERROR MUTEX UNLOCK 0\n");
// 		if (pthread_mutex_unlock(&couvert.left->fork) != 0)
// 			printf("ERROR MUTEX UNLOCK 1\n");
// 		printf("%lld %s just dropped fork\n",
// 			timestamp_max - timestamp_now, root->name);
// 		gettimeofday(&time, NULL);
// 		timestamp_now = timestamp_now + (long long int)time.tv_usec;
// 		philo_is_sleeping(root->arg.t_sleep, root->name,
// 			timestamp_now, timestamp_max);
// 		gettimeofday(&time, NULL);
// 		timestamp_now = timestamp_now + (long long int)time.tv_usec;
// 		philo_is_thinking(1, root->name, timestamp_now, timestamp_max);
// 		gettimeofday(&time, NULL);
// 		timestamp_now = timestamp_now + (long long int)time.tv_usec;
// 		usleep(200000);
// 	}
// 	printf("%lld %s just died\n", timestamp_max - timestamp_now, root->name);
// 	return (free_root_and_return(root));
// }

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
*/
