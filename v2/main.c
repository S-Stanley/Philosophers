/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:55:36 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/10 18:52:20 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*routine(void *arg)
{
	t_root	*root;

	root = (t_root *)arg;
	pthread_mutex_lock(root->g_mutex);
	printf("%s\n", root->name);
	pthread_mutex_unlock(root->g_mutex);
	free(root);
	return (arg);
}

char	*give_name(const unsigned int id)
{
	if (id == 0)
		return ("Aristote");
	if (id == 1)
		return ("Kant");
	if (id == 2)
		return ("Platon");
	if (id == 3)
		return ("Socrate");
	if (id == 4)
		return ("Nietzsche");
	if (id == 5)
		return ("Descartes");
	if (id == 6)
		return ("Confucius");
	if (id == 7)
		return ("Marx");
	if (id == 8)
		return ("Sarte");
	if (id == 9)
		return ("Epicure");
	return ("Aristote");
}

t_philo	*add_philo(unsigned int id, char *name, pthread_t thread, t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->id = id;
	new->name = name;
	new->thread = thread;
	new->next = NULL;
	if (!philo)
		return (new);
	tmp = philo;
	while (philo->next)
		philo = philo->next;
	philo->next = new;
	return (tmp);
}

t_philo	*setup_philo(t_arg arg)
{
	t_philo			*philo;
	pthread_t		threads[arg.nbr_philo];
	unsigned int	i;

	philo = NULL;
	i = 0;
	while (i < arg.nbr_philo)
	{
		philo = add_philo(i, give_name(i), threads[i], philo);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_root			*root;
	pthread_mutex_t	g_mutex;
	t_arg			arg;
	t_philo			*philo;
	t_philo			*tmp;

	if (argc != 4 && argc != 5)
		print_and_exit("Wrong number or arguments\n");
	arg = setup_arg(argc, argv);
	philo = setup_philo(arg);
	pthread_mutex_init(&g_mutex, NULL);
	root = NULL;
	tmp = philo;
	while (philo)
	{
		root = malloc(sizeof(t_root));
		root->name = philo->name;
		root->g_mutex = &g_mutex;
		pthread_create(&philo->thread, NULL, routine, root);
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
