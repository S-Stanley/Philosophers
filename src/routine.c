/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/19 17:11:19 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct s_couvert {
	t_dishes	*left;
	t_dishes	*right;
}	t_couvert;

#define ONE_SECOND		1000000
#define ONE_MINI_SECOND	1000
#define EATING			0
#define SLEEPING		1
#define THINKING		2
#define TIME_TO_DIE		410
#define TIME_TO_EAT		200
#define TIME_TO_SLEEP	200

#define FALSE			0
#define TRUE			1
#define BOOLEAN			unsigned int

pthread_mutex_t	g_mutex;

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

void	action(int action, t_root root)
{
	t_couvert		couvert;

	couvert = get_philo_fork(root.id, root.fork);
	if (action == EATING)
	{
		pthread_mutex_lock(&couvert.left->fork);
		pthread_mutex_lock(&couvert.right->fork);
		printf("philo %d is eating\n", root.id);
		usleep(root.arg.t_eat * ONE_MINI_SECOND);
		pthread_mutex_unlock(&couvert.left->fork);
		pthread_mutex_unlock(&couvert.right->fork);
	}
	else if (action == SLEEPING)
	{
		printf("philo %d is sleeping\n", root.id);
		usleep(root.arg.t_sleep * ONE_MINI_SECOND);
	}
	else
	{
		printf("philo %d is thinking\n", root.id);
	}
}

void	what_to_do(int thread_nb, t_root root)
{
	if ((thread_nb % 2) == 0)
	{
		action(EATING, root);
		action(SLEEPING, root);
		action(THINKING, root);
	}
	else
	{
		action(SLEEPING, root);
		action(THINKING, root);
		action(EATING, root);
	}
}

struct timeval	get_timeval(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

BOOLEAN	check_philo_alive(struct timeval time, struct timeval tmp, t_root root)
{
	long int	max_value_usec;
	long int	iter_time;

	max_value_usec = 999999;
	if (time.tv_sec == tmp.tv_sec)
		iter_time = time.tv_usec - tmp.tv_usec;
	else
		iter_time = time.tv_usec + (max_value_usec - tmp.tv_usec);
	iter_time = iter_time / ONE_MINI_SECOND;
	printf("*Philo %d took %ld usec out of %d\n",
		root.id, iter_time, root.arg.t_die);
	if (iter_time > root.arg.t_die)
	{
		printf("Philo %d just died\n", root.id);
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
		time = get_timeval();
		tmp = time;
		what_to_do(root->id, *root);
		gettimeofday(&time, NULL);
		time = get_timeval();
		if (!check_philo_alive(time, tmp, *root))
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
