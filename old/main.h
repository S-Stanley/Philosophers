/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 23:16:00 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 14:08:48 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_arg {
	unsigned int	nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_should_eat;
}	t_arg;

typedef struct s_philo {
	pthread_t			philo;
	unsigned int		id;
	char				*name;
	void				*next;
}	t_philo;

typedef struct s_prog {
	pthread_mutex_t		*mutex;
	t_philo				*philo;
}	t_prog;

typedef struct s_routine {
	t_philo	*this_philo;
	t_prog	prog;
	int		global;
}	t_routine;

pthread_mutex_t	g_mutex;
extern int		g_global;

void			print_and_exit(char *message);
unsigned int	ft_strlen(const char *str);
t_arg			setup_arg(int argc, char **argv);
int				ft_atoi(char *str);
void			exit_programme(char *message, t_philo *philo);
void			free_philo(t_philo *philo);
t_philo			*setup_philo(t_arg arg);
void			*routine(void	*arg);
void			create_thread_and_join_for_philo(t_prog prog, pthread_mutex_t *mutex);

#endif