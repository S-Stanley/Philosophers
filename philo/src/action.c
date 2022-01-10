/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:58:50 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/11 00:23:31 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
	On check le nombre de groupe avec nb_philo % 2
	Il faut que tous les philo du groupe mangent en meme temps
	Le groupe 3 mange toujours en dernier
	Si 1 a manger identique aue 2 et 3 alors 1 et tout son groupe mange. ensuite 2 puis 3.
	Cette algo ne fonctionne que si le nombre de groupe est de 3 (je pense)
*/

t_philo	*set_philo_ate(t_philo *philo, unsigned int id, long int time)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		if (philo->id == id)
		{
			philo->ate++;
			(void)time;
			break ;
		}
		philo = philo->next;
	}
	return (tmp);
}

BOOL	print_something(t_data *data, int content)
{
	pthread_mutex_lock(data->mutex);
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->mutex);
		return (FALSE);
	}
	if (content == 0)
		printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
	if (content == 1)
		printf("%ld philo %d is eating\n", get_time(data->time), data->id);
	if (content == 2)
		printf("%ld philo %d is sleeping\n", get_time(data->time), data->id);
	if (content == 3)
		printf("%ld philo %d is thinking\n", get_time(data->time), data->id);
	pthread_mutex_unlock(data->mutex);
	return (TRUE);
}

BOOL	eating(t_data *data, struct timeval start_time)
{
	if (!print_something(data, 0))
		return (FALSE);
	if (!print_something(data, 0))
		return (FALSE);
	if (!print_something(data, 1))
		return (FALSE);
	pthread_mutex_lock(data->mutex);
	data->philo = set_philo_ate(data->philo, data->id, get_time(data->time));
	pthread_mutex_unlock(data->mutex);
	if (!ft_sleep(data->t_eat, data, start_time))
		return (FALSE);
	return (TRUE);
}

BOOL	sleeping(t_data *data, struct timeval start_time)
{
	if (!print_something(data, 2))
		return (FALSE);
	if (!ft_sleep(data->t_sleep, data, start_time))
		return (FALSE);
	return (TRUE);
}

BOOL	thinking(t_data *data)
{
	if (!print_something(data, 3))
		return (FALSE);
	return (TRUE);
}

BOOL	smallest_eat(t_philo *philo, unsigned int id, int *stop, t_data *data)
{
	int		mine;
	int		min;
	t_philo	*tmp;

	pthread_mutex_lock(data->mutex);
	if (stop[0])
	{
		pthread_mutex_unlock(data->mutex);
		return (TRUE);
	}
	tmp = philo;
	min = -1;
	while (philo)
	{
		if (philo->id == id)
			mine = philo->ate;
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		if (min == -1)
			min = philo->ate;
		if (min != -1 && philo->ate < min)
			min = philo->ate;
		if (philo->id != id)
		{
			if (mine > philo->ate)
			{
				pthread_mutex_unlock(data->mutex);
				return (0);
			}
		}
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		if (philo->id == id)
		{
			pthread_mutex_unlock(data->mutex);
			return (1);
		}
		if (philo->ate <= min && philo->ate <= mine)
		{
			pthread_mutex_unlock(data->mutex);
			return (0);
		}
		philo = philo->next;
	}
	pthread_mutex_unlock(data->mutex);
	return (1);
}

int	guess_grp(int nb)
{
	int	group;

	if (nb == 1 || nb == 2 || nb == 3)
		return (nb);
	group = 1;
	while (nb != 0)
	{
		if (group == 3)
			group = 1;
		else
			group++;
		nb--;
	}
	return (group);
}

t_philo	*add_ate_to_philo(t_philo *philo, unsigned int id)
{
	t_philo	*tmp;

	tmp = philo;
	while (philo)
	{
		if (id == philo->id)
			philo->ate++;
		philo = philo->next;
	}
	return (tmp);
}

BOOL	did_all_ate(t_philo *philo, int grp, int *eat_round)
{
	while (philo)
	{
		if (guess_grp(philo->id) == grp)
		{
			if (eat_round[0] != philo->ate)
				return (0);
		}
		philo = philo->next;
	}
	return (1);
}

int	can_he_eat(t_data *data)
{
	int		grp;

	pthread_mutex_lock(data->mutex);
	grp = guess_grp(data->id);
	if (grp == 1 && data->ate < data->eat_round_one[0]
		&& did_all_ate(data->philo, 2, data->eat_round_two)
		&& did_all_ate(data->philo, 3, data->eat_round_three))
	{
		data->philo = add_ate_to_philo(data->philo, data->id);
		if (did_all_ate(data->philo, grp, data->eat_round_one))
			data->eat_round_two[0]++;
		pthread_mutex_unlock(data->mutex);
		return (1);
	}
	if (grp == 2 && data->ate < data->eat_round_two[0]
		&& did_all_ate(data->philo, 1, data->eat_round_one))
	{
		data->philo = add_ate_to_philo(data->philo, data->id);
		if (did_all_ate(data->philo, grp, data->eat_round_two))
			data->eat_round_three[0]++;
		pthread_mutex_unlock(data->mutex);
		return (1);
	}
	if (grp == 3 && data->ate < data->eat_round_three[0])
	{
		data->philo = add_ate_to_philo(data->philo, data->id);
		pthread_mutex_unlock(data->mutex);
		return (1);
	}
	pthread_mutex_unlock(data->mutex);
	return (0);
}

BOOL	ft_loop1(t_data *data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	// while (!smallest_eat(data->philo, data->id, data->stop, data))
	// 	usleep(1);
	while (!can_he_eat(data))
		usleep(1);
	lock_fork(data);
	if (!eating(data, start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	unlock_fork(data);
	if (guess_grp(data->id) == 3)
		data->eat_round_one[0]++;
	if (!sleeping(data, start_time))
		return (FALSE);
	if (!thinking(data))
		return (FALSE);
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(start_time, data))
		return (FALSE);
	pthread_mutex_unlock(data->mutex);
	return (TRUE);
}

BOOL	ft_loop2(t_data *data)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	if (!thinking(data))
		return (FALSE);
	if (!sleeping(data, start_time))
		return (FALSE);
	// while (!smallest_eat(data->philo, data->id, data->stop, data))
	// 	usleep(1);
	while (!can_he_eat(data))
		usleep(1);
	lock_fork(data);
	if (!eating(data, start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	unlock_fork(data);
	pthread_mutex_lock(data->mutex);
	if (!check_philo_life(start_time, data))
		return (FALSE);
	pthread_mutex_unlock(data->mutex);
	return (TRUE);
}
