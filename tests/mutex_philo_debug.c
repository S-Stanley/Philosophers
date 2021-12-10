/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_philo_debug.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:30:55 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 17:54:27 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t	g_mutex;

typedef struct s_philo {
	char		*name;
	pthread_t	thread;
	void		*next;
}	t_philo;

void	*increment(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&g_mutex);
	printf("Creating %s\n", philo->name);
	pthread_mutex_unlock(&g_mutex);
	return (arg);
}

t_philo	*add_new(char *name, t_philo *philo)
{
	t_philo	*new;
	t_philo	*tmp;

	new = malloc(sizeof(t_philo));
	new->name = name;
	new->thread = (long unsigned int)malloc(sizeof(pthread_t));
	new->next = NULL;
	if (!philo)
		return (new);
	tmp = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = new;
	return (tmp);
}

t_philo	*dup_philo(char *name)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->name = name;
	new->next = NULL;
	return (new);
}

int	main(void)
{
	char			*names[] = {"Aristote", "Socrate", "Platon", "Kant", 0};
	t_philo			*philo;
	t_philo			*tmp;
	unsigned int	i;
	t_philo			*dup;

	i = 0;
	philo = NULL;
	while (i < 4)
	{
		philo = add_new(names[i], philo);
		i++;
	}
	tmp = philo;
	pthread_mutex_init(&g_mutex, NULL);
	while (philo)
	{
		dup = dup_philo(philo->name);
		pthread_create(&philo->thread, NULL, increment, &dup);
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	pthread_mutex_destroy(&g_mutex);
	return (0);
}
