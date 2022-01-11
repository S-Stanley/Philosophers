/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:00:31 by sserbin           #+#    #+#             */
/*   Updated: 2022/01/11 21:03:44 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iswhitespace(char c)
{
	if (c >= 9 && c <= 13)
	{
		return (1);
	}
	else if (c == 32)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	long long	pos;

	i = 0;
	pos = 1;
	res = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pos = pos * -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res > 2147483647 && pos == 1)
			return (-1);
		if (res > 2147483648 && pos == -1)
			return (-1);
	}
	return (res * pos);
}
