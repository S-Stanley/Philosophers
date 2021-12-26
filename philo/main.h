/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:29:35 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:49:40 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define ONE_MINI_SECOND	1000
# define EATING				0
# define SLEEPING			1
# define THINKING			2

# define FALSE				0
# define TRUE				1
# define BOOLEAN			unsigned int

# define PHILO_TAKE_FORK 	0
# define PHILO_EAT			1
# define PHILO_SLEEP		2
# define PHILO_THINK		3

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
	char			*name;
	pthread_t		thread;
	void			*next;
}	t_philo;

typedef struct s_arg {
	unsigned int	nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_should_eat;
}	t_arg;

typedef struct s_root {
	pthread_mutex_t	*g_mutex;
	char			*name;
	unsigned int	id;
	t_dishes		*fork;
	t_arg			arg;
	t_philo			*philo;
	int				*stop;
	long long int	*total_time;
}	t_root;

typedef struct s_create_root {
	int				*stop;
	pthread_mutex_t	*g_mutex;
	t_philo			*start;
	t_dishes		*fork;
	long long int	*total_time;
}	t_create_root;

t_arg			setup_arg(int argc, char **argv);
int				print_and_exit(char *message);
int				ft_atoi(char *str);
unsigned int	ft_strlen(const char *str);
void			*routine(void *arg);
void			free_philo(t_philo *philo);
char			*setup_philo_routine(pthread_mutex_t *g_mutex,
					t_philo *philo, t_dishes *fork, t_arg arg);
t_philo			*setup_philo(t_arg arg);
char			*free_root_and_return_null(t_root *root);
void			*free_root_and_return(t_root *root);
void			*routine2(void *arg);
BOOLEAN			check_error_arg(int argc, char **argv);
BOOLEAN			print_str(int type, struct timeval tmp, t_root root,
					long long int *tt);
long int		get_timestamp(struct timeval tmp);
BOOLEAN			check_philo_alive(struct timeval tmp, t_root root);
t_couvert		get_philo_fork(unsigned int id, t_dishes *fork);
void			lock_fork(t_root root);
void			unlock_fork(t_root root);
int				*get_stop_value(void);
char			*give_name(const unsigned int id);
long long int	*get_total_time(void);

#endif