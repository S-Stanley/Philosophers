/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:29:35 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 18:45:32 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_root {
	pthread_mutex_t	*g_mutex;
	char			*name;
}	t_root;

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

t_arg			setup_arg(int argc, char **argv);
void			print_and_exit(char *message);
int				ft_atoi(char *str);
unsigned int	ft_strlen(const char *str);

#endif