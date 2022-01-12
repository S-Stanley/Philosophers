/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:48:31 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/12 23:40:56 by sserbin          ###   ########.fr       */
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

void	lock_fork(t_data *data)
{
	if (data->id == data->nbr_philo)
	{
		pthread_mutex_lock(&data->forks[data->id - 1]);
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %d has taken a fork\n",
			get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		pthread_mutex_lock(&data->forks[0]);
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %d has taken a fork\n",
			get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
	}
	else
	{
		pthread_mutex_lock(&data->forks[data->id - 1]);
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %d has taken a fork\n",
			get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		pthread_mutex_lock(&data->forks[data->id]);
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %d has taken a fork\n",
			get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
	}	
}

void	eating(t_data *data, struct timeval *start_time)
{
	lock_fork(data);
	if (get_time(*start_time) >= data->t_die)
	{
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %u died\n", get_time(*start_time), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		exit(0);
	}
	pthread_mutex_lock(data->commun_mutex);
	printf("%ld philo %d is eating\n",
		get_time(data->prog_time_start), data->id);
	pthread_mutex_unlock(data->commun_mutex);
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
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %d is sleeping\n",
			get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		usleep(data->t_sleep * 1000);
		pthread_mutex_lock(data->commun_mutex);
		printf("%ld philo %d is thinking\n",
			get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
	}
	free(arg);
	return (arg);
}

void	ft_philo(t_arg arg)
{
	pthread_t		threads[arg.nbr_philo];
	void			*forks;
	unsigned int	i;
	t_data			*data;
	struct timeval	prog_time_start;
	pthread_mutex_t	*commun_mutex;

	commun_mutex = malloc(sizeof(pthread_mutex_t));
	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * arg.nbr_philo);
	init_mutex(forks, arg.nbr_philo);
	pthread_mutex_init(commun_mutex, NULL);
	gettimeofday(&prog_time_start, NULL);
	while (i < arg.nbr_philo)
	{
		data = malloc(sizeof(t_data));
		data->id = i + 1;
		data->forks = forks;
		data->prog_time_start = prog_time_start;
		data->t_eat = arg.t_eat;
		data->t_sleep = arg.t_sleep;
		data->t_die = arg.t_die;
		data->max_t_eat = arg.max_t_eat;
		data->nbr_philo = arg.nbr_philo;
		data->commun_mutex = commun_mutex;
		pthread_create(&threads[i], NULL, routine, data);
		i++;
	}
	i = 0;
	while (i < arg.nbr_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(commun_mutex);
	destroy_mutex(forks, arg.nbr_philo);
	free(forks);
	free(commun_mutex);
}

int	main(int argc, char **argv)
{
	t_arg			arg;

	if (check_error_arg(argc, argv))
		return (0);
	arg = setup_arg(argc, argv);
	if (!is_arg_correct(argv, arg, argc))
		return (0);
	ft_philo(arg);
	return (0);
}
