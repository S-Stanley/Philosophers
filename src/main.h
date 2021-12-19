/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:29:35 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/19 18:06:59 by sserbin          ###   ########.fr       */
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

typedef struct s_dishes {
	pthread_mutex_t	fork;
	void			*next;
	unsigned int	id;
}	t_dishes;

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
}	t_root;

t_arg			setup_arg(int argc, char **argv);
int				print_and_exit(char *message);
int				ft_atoi(char *str);
unsigned int	ft_strlen(const char *str);
void			*routine(void *arg);
void			free_philo(t_philo *philo);
char			*setup_philo_routine(pthread_mutex_t *g_mutex, t_philo *philo, t_dishes *fork, t_arg arg);
t_philo			*setup_philo(t_arg arg);
char			*free_root_and_return_null(t_root *root);
void			*free_root_and_return(t_root *root);
void			*routine2(void *arg);

#endif