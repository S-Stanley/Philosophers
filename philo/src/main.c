/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:48:31 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 01:40:18 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

BOOL	check_philo_life(struct timeval start_time, t_data *data)
{
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	if (get_time(start_time) > (unsigned int)data->t_die)
	{
		data->stop[0] = 1;
		printf("%ld\n", get_time(start_time));
		printf("%ld philo %d died\n", get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	return (TRUE);
}

BOOL	ft_sleep(long int sleepingtime, t_data *data, struct timeval start_time)
{
	int		timeleft;

	timeleft = data->t_die - get_time(start_time);
	if (timeleft > sleepingtime)
		usleep(sleepingtime * 1000);
	else
	{
		while (sleepingtime > 0)
		{
			pthread_mutex_lock(data->commun_mutex);
			if (!check_philo_life(start_time, data))
				return (FALSE);
			pthread_mutex_unlock(data->commun_mutex);
			usleep(10 * 1000);
			sleepingtime = sleepingtime - 10;
		}
	}
	return (TRUE);
}

BOOL	print_something(t_data *data, int content, struct timeval *start_time)
{
	pthread_mutex_lock(data->commun_mutex);
	if (get_time(*start_time) >= data->t_die)
	{
		printf("%ld philo %u died\n", get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		exit(0);
	}
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	if (content == 0)
		printf("%ld philo %u has taken a fork\n",
			get_time(data->prog_time_start), data->id);
	if (content == 1)
		printf("%ld philo %u is eating\n",
			get_time(data->prog_time_start), data->id);
	if (content == 2)
		printf("%ld philo %u is sleeping\n",
			get_time(data->prog_time_start), data->id);
	if (content == 3)
		printf("%ld philo %u is thinking\n",
			get_time(data->prog_time_start), data->id);
	pthread_mutex_unlock(data->commun_mutex);
	return (TRUE);
}

void	lock_fork(t_data *data, struct timeval *start_time)
{
	if (data->id == data->nbr_philo)
	{
		pthread_mutex_lock(&data->forks[data->id - 1]);
		if (!print_something(data, 0, start_time))
			return ;
		pthread_mutex_lock(&data->forks[0]);
		if (!print_something(data, 0, start_time))
			return ;
	}
	else
	{
		pthread_mutex_lock(&data->forks[data->id - 1]);
		if (!print_something(data, 0, start_time))
			return ;
		pthread_mutex_lock(&data->forks[data->id]);
		if (!print_something(data, 0, start_time))
			return ;
	}	
}

void	eating(t_data *data, struct timeval *start_time)
{
	lock_fork(data, start_time);
	if (get_time(*start_time) >= data->t_die)
	{
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %u died\n", get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		exit(0);
	}
	if (!print_something(data, 1, start_time))
		return ;
	// printf("**** philo %d max %ld ****\n", data->id, get_time(*start_time));
	gettimeofday(start_time, NULL);
	usleep(data->t_eat * 1000);
	pthread_mutex_unlock(&data->forks[data->id - 1]);
	if (data->id == data->nbr_philo)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[data->id]);
}

void	*routine(void *arg)
{
	t_data			*data;
	struct timeval	start_time;
	int				ate;

	data = (t_data *)arg;
	gettimeofday(&start_time, NULL);
	if (data->id % 2)
		usleep(200 * 1000);
	ate = 0;
	while (1)
	{
		eating(data, &start_time);
		ate++;
		if (data->max_t_eat > 0 && ate == data->max_t_eat)
			break ;
		if (!print_something(data, 2, &start_time))
			break ;
		usleep(data->t_sleep * 1000);
		if (!print_something(data, 3, &start_time))
			break ;
	}
	free(arg);
	return (arg);
}

t_data	*init_philo(pthread_mutex_t *forks, struct timeval prog_time_start, pthread_mutex_t *commun_mutex, t_arg arg)
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	data->forks = forks;
	data->prog_time_start = prog_time_start;
	data->t_eat = arg.t_eat;
	data->t_sleep = arg.t_sleep;
	data->t_die = arg.t_die;
	data->max_t_eat = arg.max_t_eat;
	data->nbr_philo = arg.nbr_philo;
	data->commun_mutex = commun_mutex;
	return (data);
}

void	ft_philo(t_arg arg, int *stop, pthread_mutex_t *commun_mutex)
{
	pthread_t		threads[arg.nbr_philo];
	void			*forks;
	int				i;
	struct timeval	prog_time_start;
	t_data			*data;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * arg.nbr_philo);
	init_mutex(forks, arg.nbr_philo);
	gettimeofday(&prog_time_start, NULL);
	while ((unsigned int)++i < arg.nbr_philo)
	{
		data = init_philo(forks, prog_time_start, commun_mutex, arg);
		data->stop = stop;
		data->id = i + 1;
		pthread_create(&threads[i], NULL, routine, data);
	}
	i = -1;
	while ((unsigned int)++i < arg.nbr_philo)
	{
		pthread_join(threads[i], NULL);
	}
	destroy_mutex(forks, arg.nbr_philo);
	free(forks);
}

void	one_philo(t_arg arg, int *stop, pthread_mutex_t *commun_mutex)
{
	struct timeval	start_time;
	t_data			*data;

	data = malloc(sizeof(t_data));
	gettimeofday(&start_time, NULL);
	data->t_die = arg.t_die;
	data->commun_mutex = commun_mutex;
	data->prog_time_start = start_time;
	data->stop = stop;
	data->id = 1;
	printf("%ld philo %d as taken a fork\n", get_time(start_time), data->id);
	ft_sleep(data->t_die + 1, data, start_time);
	free(data);
}

int	main(int argc, char **argv)
{
	t_arg			arg;
	pthread_mutex_t	*commun_mutex;
	int				*stop;

	if (check_error_arg(argc, argv))
		return (0);
	arg = setup_arg(argc, argv);
	if (!is_arg_correct(argv, arg, argc))
		return (0);
	stop = malloc(sizeof(int));
	stop[0] = 0;
	commun_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(commun_mutex, NULL);
	if (arg.nbr_philo == 1)
		one_philo(arg, stop, commun_mutex);
	else
		ft_philo(arg, stop, commun_mutex);
	pthread_mutex_destroy(commun_mutex);
	free(commun_mutex);
	free(stop);
	return (0);
}
