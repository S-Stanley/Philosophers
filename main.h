/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 23:16:00 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/06 19:51:00 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void			print_and_exit(char *message);
unsigned int	ft_strlen(const char *str);

#endif