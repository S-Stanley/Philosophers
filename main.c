/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 23:15:24 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/08 21:38:38 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct s_philo {
	pthread_t		philo;
	unsigned int	id;
	char			*name;
	void			*next;
}	t_philo;

t_philo	*create_philo(unsigned int id, char *name)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		exit_programme();
	lst->id = id;
	lst->name = name;
	lst->next = NULL;
	return (lst);
}

t_philo	*push_back_philo(t_philo *lst, unsigned int id, char *name)
{
	t_philo	*new;
	t_philo	*tmp;

	new = create_philo(id, name);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst)
		lst = lst->next;
	lst = new;
	return (tmp);
}

t_philo	*setup_philo(t_arg arg)
{
	unsigned int	i;
	t_philo			*lst;

	i = 0;
	lst = NULL;
	while (i < arg.nbr_philo)
	{
		lst = push_back_philo(lst, i, "Aristote");
		i++;
	}
	return (lst);
}

int	main(int argc, char **argv)
{
	t_arg	arg;
	t_philo	*philo;

	if (argc != 4 && argc != 5)
		print_and_exit("Wrong number or arguments");
	arg = setup_arg(argc, argv);
	philo = setup_philo(arg);
	return (0);
}
