/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:52:15 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/04 00:56:14 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_philo_life(struct timeval start_time, t_data *data)
{
	if (get_time(start_time) > data->t_die)
	{
		printf("%ld philo %d died\n", get_time(start_time), data->id);
		pthread_mutex_unlock(data->mutex);
		exit(0);
	}
}

void	*routine(void *arg)
{
	t_data			*data;
	struct timeval	time;
	struct timeval	start_time;
	int				ate;

	ate = 0;
	data = (t_data *)arg;
	while (TRUE)
	{
		gettimeofday(&start_time, NULL);
		lock_fork(data);
		eating(data, start_time);
		unlock_fork(data);
		sleeping(data, start_time);
		thinking(data);
		pthread_mutex_lock(data->mutex);
		check_philo_life(start_time, data);
		pthread_mutex_unlock(data->mutex);
		ate++;
		if (ate == data->max_t_eat)
			break ;
	}
	free(arg);
	return (arg);
}

long int	get_time(struct timeval time)
{
	struct timeval	now;
	long int		max;

	max = 999999;
	gettimeofday(&now, NULL);
	if (now.tv_sec == time.tv_sec)
		return ((now.tv_usec - time.tv_usec) / 1000);
	else
		return ((
				((max - time.tv_usec) + now.tv_usec)
				+ ((now.tv_sec - time.tv_sec -1) * max)) / 1000);
}

void	ft_sleep(long int sleepingtime, t_data *data, struct timeval start_time)
{
	int		timeleft;

	timeleft = data->t_die - get_time(start_time);
	if (timeleft > sleepingtime)
		usleep(sleepingtime * 1000);
	else
	{
		while (sleepingtime > 0)
		{
			check_philo_life(start_time, data);
			usleep(10 * 1000);
			sleepingtime = sleepingtime - 10;
		}
	}
}

void	eating(t_data *data, struct timeval start_time)
{
	printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
	printf("%ld philo %d has taken a fork\n", get_time(data->time), data->id);
	printf("%ld philo %d is eating\n", get_time(data->time), data->id);
	ft_sleep(data->t_eat, data, start_time);
}

void	sleeping(t_data *data, struct timeval start_time)
{
	printf("%ld philo %d is sleeping\n", get_time(data->time), data->id);
	ft_sleep(data->t_sleep, data, start_time);
}

void	thinking(t_data *data)
{
	printf("%ld philo %d is thinking\n", get_time(data->time), data->id);
}

t_data	*create_data(int id, struct timeval time, pthread_mutex_t *mutex, t_arg arg, t_dishes *fork)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->id = id;
	data->time = time;
	data->mutex = mutex;
	data->t_sleep = arg.t_sleep;
	data->t_eat = arg.t_eat;
	data->t_die = arg.t_die;
	data->max_t_eat = arg.max_t_eat;
	data->fork = fork;
	return (data);
}

long int	*create_timestamp(void)
{
	long int	*time;

	time = malloc(sizeof(long int));
	time[0] = 0;
	return (time);
}

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

int	main(int argc, char **argv)
{
	struct timeval	time;
	pthread_mutex_t	mutex;
	t_arg			arg;
	t_philo			*philo;
	t_philo			*tmp;
	t_dishes		*fork;

	if (check_error_arg(argc, argv))
		return (0);
	arg = setup_arg(argc, argv);
	philo = setup_philo(arg);
	fork = init_mutex(arg.nbr_philo);
	gettimeofday(&time, NULL);
	tmp = philo;
	while (philo)
	{
		pthread_create(&philo->thread, NULL, routine, create_data(philo->id, time, &mutex, arg, fork));
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	destroy_mutex(fork);
	return (0);
}
