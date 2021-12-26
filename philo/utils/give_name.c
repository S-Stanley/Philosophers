/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:27:07 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/26 17:28:23 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
