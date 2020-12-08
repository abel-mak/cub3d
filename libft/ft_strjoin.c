/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:04:41 by abel-mak          #+#    #+#             */
/*   Updated: 2020/10/19 09:46:14 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	j = 0;
	i = 0;
	if (p != NULL)
	{
		while (s1[i] != '\0')
		{
			p[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
		{
			p[i] = s2[j];
			j++;
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}
