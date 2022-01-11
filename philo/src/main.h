/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:01:02 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/11 23:09:06 by sserbin          ###   ########.fr       */
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
	int				ate;
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
	int				*stop;
	t_philo			*philo;
	int				*eat_round_one;
	int				*eat_round_two;
	int				*eat_round_three;
	int				ate;
}	t_data;

typedef struct s_arg {
	unsigned int	nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_t_eat;
}	t_arg;

long int	*create_timestamp(void);
void		*routine(void *arg);
long int	get_time(struct timeval time);
BOOL		check_philo_life(struct timeval start_time, t_data *data);
BOOL		ft_sleep(long int sleepingtime, t_data *data,
				struct timeval start_time);
int			ft_atoi(char *str);
t_arg		setup_arg(int argc, char **argv);
BOOL		check_error_arg(int argc, char **argv);
t_philo		*setup_philo(t_arg arg);
void		lock_fork(t_data *data);
void		unlock_fork(t_data *data);
t_dishes	*init_mutex(int nb);
void		destroy_mutex(t_dishes *fork);
void		*routine(void *arg);
t_dishes	*add_fork(t_dishes *fork, unsigned int i);
void		free_dishes(t_dishes *fork);
void		free_for_exit(t_dishes *fork, t_philo *philo);
void		free_philo(t_philo *philo);
BOOL		ft_loop(t_data *data, struct timeval *start_time);
int			*create_stop_var(void);
BOOL		print_something(t_data *data, int content);
t_couvert	get_philo_fork(unsigned int id, t_dishes *fork);
BOOL		is_arg_correct(char **argv, t_arg arg, int argc);
int			count_len_philo(t_philo *philo);
void		wait_a_little(t_data *data);

#endif