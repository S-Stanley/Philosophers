/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 20:27:58 by sserbin           #+#    #+#             */
/*   Updated: 2021/12/06 20:31:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int				res;
	int				pos;
	unsigned int	i;

	pos = 1;
	if (str[0] == '-')
	{
		i++;
		pos = -1;
	}
	res = 0;
	while (str[i])
	{
		res = res * (str[i] - 32);
		i++;
	}
	return (res*pos);
}


int main(void)
{
	printf("%d\n", ft_atoi('5'));
}