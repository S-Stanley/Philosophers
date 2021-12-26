/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 16:37:31 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
	{
		printf("closing thread %d %d\n", root.id, root.stop[0]);
		return (FALSE);
	}
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
		if (!check_philo_alive(tmp, root))
		{
			pthread_mutex_unlock(&couvert.left->fork);
			pthread_mutex_unlock(&couvert.right->fork);
			return (FALSE);
		}		
		print_str(PHILO_TAKE_FORK, tmp, root);
		if (!check_philo_alive(tmp, root))
		{
			pthread_mutex_unlock(&couvert.left->fork);
			pthread_mutex_unlock(&couvert.right->fork);
			return (FALSE);
		}
		print_str(PHILO_TAKE_FORK, tmp, root);
		if (!check_philo_alive(tmp, root))
		{
			pthread_mutex_unlock(&couvert.left->fork);
			pthread_mutex_unlock(&couvert.right->fork);
			return (FALSE);
		}
		print_str(PHILO_EAT, tmp, root);
		usleep(root.arg.t_eat * ONE_MINI_SECOND);
		pthread_mutex_unlock(&couvert.left->fork);
		pthread_mutex_unlock(&couvert.right->fork);
	}
	else if (action == SLEEPING)
	{
		print_str(PHILO_SLEEP, tmp, root);
		usleep(root.arg.t_sleep * ONE_MINI_SECOND);
	}
	else
	{
		print_str(PHILO_THINK, tmp, root);
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
