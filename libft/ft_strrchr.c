/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:37:38 by abel-mak          #+#    #+#             */
/*   Updated: 2019/10/23 19:37:27 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			res = (char*)(s + i);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return (char*)(s + i);
	}
	return (res);
}
