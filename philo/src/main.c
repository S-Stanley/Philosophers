/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 23:48:31 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 22:07:18 by sserbin          ###   ########.fr       */
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
		return (exit_err_main(stop, commun_mutex, 0));
	if (pthread_mutex_init(commun_mutex, NULL) != 0)
		return (exit_err_main(stop, commun_mutex, 1));
	if (arg.nbr_philo == 1)
		one_philo(arg, stop, commun_mutex);
	else
		ft_philo(arg, stop, commun_mutex);
	pthread_mutex_destroy(commun_mutex);
	return (exit_err_main(stop, commun_mutex, 1));
}
