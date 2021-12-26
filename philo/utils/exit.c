/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:49:35 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 16:37:48 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	print_and_exit(char *message)
{
	write(1, "Error\n", ft_strlen("Error\n"));
	write(1, message, ft_strlen(message));
	return (1);
}
