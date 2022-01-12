/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:53:19 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/12 23:08:43 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

// # define NB_PHILO		4
// # define TIME_TO_DIE	410
// # define TIME_TO_SLEEP	200
// # define TIME_TO_EAT	200
// # define MAX_TIME_EAT	5
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
}	t_data;

typedef struct s_arg {
	unsigned int	nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_t_eat;
}	t_arg;

int		ft_strlen(const char *str);
BOOL	is_arg_correct(char **argv, t_arg arg, int argc);
BOOL	check_error_arg(int argc, char **argv);
t_arg	setup_arg(int argc, char **argv);
void	init_mutex(pthread_mutex_t *forks, unsigned int nbr_philo);
void	destroy_mutex(pthread_mutex_t *forks, unsigned int nbr_philo);
int		ft_atoi(const char *str);

#endif