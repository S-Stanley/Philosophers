/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:01:02 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/04 00:30:31 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define TRUE 	1
# define FALSE	0
# define BOOL	int

typedef struct s_dishes {
	pthread_mutex_t	fork;
	void			*next;
	unsigned int	id;
}	t_dishes;

typedef struct s_couvert {
	t_dishes	*left;
	t_dishes	*right;
}	t_couvert;

typedef struct s_philo {
	unsigned int	id;
	pthread_t		thread;
	void			*next;
}	t_philo;

typedef struct s_data {
	int				id;
	pthread_mutex_t	*mutex;
	struct timeval	time;
	int				t_sleep;
	int				t_eat;
	int				t_die;
	int				max_t_eat;
	t_dishes		*fork;
}	t_data;

typedef struct s_arg {
	unsigned int	nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_t_eat;
}	t_arg;

long int	*create_timestamp(void);
t_data		*create_data(int id, struct timeval time,
				pthread_mutex_t *mutex, t_arg arg, t_dishes *fork);
void		*routine(void *arg);
void		eating(t_data *data, struct timeval start_time);
void		sleeping(t_data *data, struct timeval start_time);
void		thinking(t_data *data);
long int	get_time(struct timeval time);
void		check_philo_life(struct timeval start_time, t_data *data);
void		ft_sleep(long int sleepingtime, t_data *data,
				struct timeval start_time);
int			ft_atoi(char *str);
t_arg		setup_arg(int argc, char **argv);
BOOL		check_error_arg(int argc, char **argv);
t_philo		*setup_philo(t_arg arg);
void		lock_fork(t_data *data);
void		unlock_fork(t_data *data);

#endif