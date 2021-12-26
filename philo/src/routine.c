/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:57:04 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:49:16 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

BOOLEAN	check_philo_alive(struct timeval tmp, t_root root)
{
	long int	iter_time;

	iter_time = get_timestamp(tmp);
	if (iter_time > root.arg.t_die)
	{
		printf("%ld %d died\n", get_timestamp(tmp), root.id);
		root.stop[0] = 1;
		unlock_fork(root);
		return (FALSE);
	}
	if (root.stop[0])
	{
		printf("closing thread %d %d\n", root.id, root.stop[0]);
		unlock_fork(root);
		return (FALSE);
	}
	return (TRUE);
}

BOOLEAN	action(	int action, t_root root, struct timeval tmp,
				long long int *total_time)
{
	t_couvert		couvert;

	couvert = get_philo_fork(root.id, root.fork);
	if (!check_philo_alive(tmp, root))
		return (FALSE);
	if (action == EATING)
	{
		lock_fork(root);
		if (!print_str(PHILO_TAKE_FORK, tmp, root, total_time)
			|| !print_str(PHILO_TAKE_FORK, tmp, root, total_time)
			|| !print_str(PHILO_EAT, tmp, root, total_time)
		)
			return (FALSE);
		usleep(root.arg.t_eat * ONE_MINI_SECOND);
		unlock_fork(root);
	}
	else if (action == SLEEPING)
	{
		if (!print_str(PHILO_SLEEP, tmp, root, total_time))
			return (FALSE);
		usleep(root.arg.t_sleep * ONE_MINI_SECOND);
	}
	else
		print_str(PHILO_THINK, tmp, root, total_time);
	return (TRUE);
}

BOOLEAN	what_to_do(	int thread_nb, t_root root, struct timeval tmp,
					long long int *total_time)
{
	if ((thread_nb % 2) == 0)
	{
		if (!action(EATING, root, tmp, total_time))
			return (FALSE);
		if (!action(SLEEPING, root, tmp, total_time))
			return (FALSE);
		if (!action(THINKING, root, tmp, total_time))
			return (FALSE);
	}
	else
	{
		if (!action(SLEEPING, root, tmp, total_time))
			return (FALSE);
		if (!action(THINKING, root, tmp, total_time))
			return (FALSE);
		if (!action(EATING, root, tmp, total_time))
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
		if (!what_to_do(root->id, *root, tmp, root->total_time))
			return (arg);
		if (!check_philo_alive(tmp, *root))
			return (arg);
	}
	return (arg);
}
