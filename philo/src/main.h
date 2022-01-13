/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:53:19 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/13 19:24:47 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define BOOL	int
# define TRUE	1
# define FALSE	0

typedef struct s_data {
	unsigned int	id;
	pthread_mutex_t	*forks;
	struct timeval	prog_time_start;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_t_eat;
	unsigned int	nbr_philo;
	pthread_mutex_t	*commun_mutex;
	int				*stop;
	pthread_t		*thread;
	struct s_data	*next;
}	t_data;

typedef struct s_arg {
	unsigned int	nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_t_eat;
}	t_arg;

int			ft_strlen(const char *str);
BOOL		is_arg_correct(char **argv, t_arg arg, int argc);
BOOL		check_error_arg(int argc, char **argv);
t_arg		setup_arg(int argc, char **argv);
BOOL		init_mutex(pthread_mutex_t *forks, unsigned int nbr_philo);
void		destroy_mutex(pthread_mutex_t *forks, unsigned int nbr_philo);
int			ft_atoi(const char *str);
void		one_philo(t_arg arg, int *stop, pthread_mutex_t *commun_mutex);
long int	get_time(struct timeval time);
BOOL		check_philo_life(struct timeval start_time, t_data *data);
BOOL		ft_sleep(long int sleepingtime,
				t_data *data, struct timeval start_time);

#endif