/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:33:57 by abel-mak          #+#    #+#             */
/*   Updated: 2020/10/20 11:09:37 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && res > (res * 10) + (sign * (str[i] - '0')))
			return (-1);
		else if (sign == -1 && res < (res * 10 + sign * (str[i] - '0')))
			return (0);
		res = res * 10 + sign * (str[i] - '0');
		i++;
	}
	return (res);
}
