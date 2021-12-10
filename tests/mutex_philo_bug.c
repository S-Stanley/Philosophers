/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_philo_bug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:15:02 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 15:20:12 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct s_philo {
	char		*name;
	pthread_t	thread;
	void		*next;
}	t_philo;

typedef struct s_root {
	t_philo			*philo;
	pthread_mutex_t	mutex;
}	t_root;

void	*increment(void *arg)
{
	t_root			*root;
	void			*ptr;

	root = (t_root *)arg;
	ptr = &root->mutex;
	pthread_mutex_lock(&root->mutex);
	printf("Creating %s %p\n", root->philo->name, ptr);
	pthread_mutex_unlock(&root->mutex);
	return (arg);
}

t_philo	*add_new(char *name, t_philo *philo)
{
	t_philo	*new;
	t_philo	*tmp;

	new = malloc(sizeof(t_philo));
	new->name = name;
	new->next = NULL;
	if (!philo)
		return (new);
	tmp = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = new;
	return (tmp);
}

int	main(void)
{
	char			*names[] = {"Aristote", "Socrate", "Platon", "Kant", 0};
	t_philo			*philo;
	t_philo			*tmp;
	unsigned int	i;
	t_root			root;
	void			*ptr;

	i = 0;
	philo = NULL;
	while (i < 4)
	{
		philo = add_new(names[i], philo);
		i++;
	}
	tmp = philo;
	root.philo = philo;
	ptr = &root.mutex;
	pthread_mutex_init(&root.mutex, NULL);
	printf("Adresse mutex %p\n", (void *)ptr);
	while (philo)
	{
		root.philo = philo;
		pthread_create(&philo->thread, NULL, increment, &root);
		philo = philo->next;
	}
	philo = tmp;
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	pthread_mutex_destroy(&root.mutex);
	return (0);
}
