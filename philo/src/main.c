/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:48:31 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 19:25:29 by sserbin          ###   ########.fr       */
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
	if (pthread_mutex_lock(data->commun_mutex) != 0)
		return (FALSE);
	if (data->stop[0])
	{
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	if (get_time(*start_time) >= data->t_die)
	{
		data->stop[0] = 1;
		printf("%ld philo %u died\n", get_time(data->prog_time_start), data->id);
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
	if (pthread_mutex_unlock(data->commun_mutex) != 0)
		return (FALSE);
	return (TRUE);
}

BOOL	lock_fork(t_data *data, struct timeval *start_time)
{
	if (data->id == data->nbr_philo)
	{
		if (pthread_mutex_lock(&data->forks[data->id - 1]) != 0)
			return (FALSE);
		if (!print_something(data, 0, start_time))
		{
			pthread_mutex_unlock(&data->forks[data->id - 1]);
			return (FALSE);
		}
		if (pthread_mutex_lock(&data->forks[0]) != 0)
		{
			pthread_mutex_unlock(&data->forks[data->id - 1]);
			return (FALSE);
		}
		if (!print_something(data, 0, start_time))
		{
			pthread_mutex_unlock(&data->forks[data->id - 1]);
			pthread_mutex_unlock(&data->forks[data->id]);
			return (FALSE);
		}
	}
	else
	{
		if (pthread_mutex_lock(&data->forks[data->id - 1]) != 0)
			return (FALSE);
		if (!print_something(data, 0, start_time))
		{
			pthread_mutex_unlock(&data->forks[data->id - 1]);
			return (FALSE);
		}
		if (pthread_mutex_lock(&data->forks[data->id]) != 0)
		{
			pthread_mutex_unlock(&data->forks[data->id - 1]);
			return (FALSE);
		}
		if (!print_something(data, 0, start_time))
		{
			pthread_mutex_unlock(&data->forks[data->id - 1]);
			pthread_mutex_unlock(&data->forks[data->id]);
			return (FALSE);
		}
	}
	return (TRUE);
}

void	unlock_fork(t_data *data)
{
	pthread_mutex_unlock(&data->forks[data->id - 1]);
	if (data->id == data->nbr_philo)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[data->id]);
}

BOOL	eating(t_data *data, struct timeval *start_time)
{
	if (!lock_fork(data, start_time))
		return (FALSE);
	if (get_time(*start_time) >= data->t_die)
	{
		if (pthread_mutex_lock(data->commun_mutex) != 0)
			return (FALSE);
		printf("%ld philo %u died\n", get_time(data->prog_time_start), data->id);
		pthread_mutex_unlock(data->commun_mutex);
		return (FALSE);
	}
	if (!print_something(data, 1, start_time))
	{
		unlock_fork(data);
		return (FALSE);
	}
	if (gettimeofday(start_time, NULL) == -1)
		return (FALSE);
	ft_sleep(data->t_eat, data, *start_time);
	unlock_fork(data);
	return (TRUE);
}

void	*routine(void *arg)
{
	t_data			*data;
	struct timeval	start_time;
	int				ate;

	data = (t_data *)arg;
	if (gettimeofday(&start_time, NULL) == -1)
	{
		free(arg);
		return (arg);
	}
	if (data->id % 2)
		ft_sleep(data->t_eat, data, start_time);
	ate = 0;
	while (1)
	{
		if (!eating(data, &start_time))
			break ;
		ate++;
		if (data->max_t_eat > 0 && ate == data->max_t_eat)
			break ;
		if (!print_something(data, 2, &start_time))
			break ;
		ft_sleep(data->t_sleep, data, start_time);
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
	if (!data)
		return (NULL);
	data->forks = forks;
	data->prog_time_start = prog_time_start;
	data->t_eat = arg.t_eat;
	data->t_sleep = arg.t_sleep;
	data->t_die = arg.t_die;
	data->max_t_eat = arg.max_t_eat;
	data->nbr_philo = arg.nbr_philo;
	data->commun_mutex = commun_mutex;
	data->next = NULL;
	data->thread = malloc(sizeof(pthread_t));
	return (data);
}

t_data	*add_tmp(t_data *buffer, t_data *new)
{
	t_data	*tmp;

	if (!buffer)
		return (new);
	tmp = buffer;
	while (buffer->next)
		buffer = buffer->next;
	buffer->next = new;
	return (tmp);
}

void	free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data->next;
		free(data);
		data = tmp;
	}
}

void	ft_philo(t_arg arg, int *stop, pthread_mutex_t *commun_mutex)
{
	void			*forks;
	int				i;
	struct timeval	prog_time_start;
	t_data			*data;
	t_data			*tmp;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * arg.nbr_philo);
	if (!forks)
		return ;
	if (!init_mutex(forks, arg.nbr_philo))
	{
		free(forks);
		return ;
	}
	if (gettimeofday(&prog_time_start, NULL) == -1)
	{
		destroy_mutex(forks, arg.nbr_philo);
		free(forks);
	}
	tmp = NULL;
	while ((unsigned int)++i < arg.nbr_philo)
	{
		data = init_philo(forks, prog_time_start, commun_mutex, arg);
		if (!data)
		{
			destroy_mutex(forks, arg.nbr_philo);
			tmp = NULL;
			free_data(tmp);
			free(forks);
			return ;
		}
		data->stop = stop;
		data->id = i + 1;
		tmp = add_tmp(tmp, data);
		if (pthread_create(data->thread, NULL, routine, data) != 0)
		{
			stop[0] = 1;
			destroy_mutex(forks, arg.nbr_philo);
			free(forks);
			return ;
		}
	}
	i = -1;
	while ((unsigned int)++i < arg.nbr_philo)
	{
		if (pthread_join(*tmp->thread, NULL) != 0)
		{
			stop[0] = 1;
			break ;
		}
		tmp = tmp->next;
	}
	destroy_mutex(forks, arg.nbr_philo);
	free(forks);
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
	if (!stop)
		return (0);
	stop[0] = 0;
	commun_mutex = malloc(sizeof(pthread_mutex_t));
	if (!commun_mutex)
	{
		free(stop);
		return (0);
	}
	if (pthread_mutex_init(commun_mutex, NULL) != 0)
	{
		free(commun_mutex);
		free(stop);
		return (0);
	}
	if (arg.nbr_philo == 1)
		one_philo(arg, stop, commun_mutex);
	else
		ft_philo(arg, stop, commun_mutex);
	pthread_mutex_destroy(commun_mutex);
	free(commun_mutex);
	free(stop);
	return (0);
}
