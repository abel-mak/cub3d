/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:18:10 by abel-mak          #+#    #+#             */
/*   Updated: 2019/11/14 11:02:53 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (s == NULL)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	p = (char*)malloc(sizeof(char) * (len + 1));
	if (p != NULL)
	{
		i = 0;
		while (i < len && s[start] != '\0')
		{
			p[i] = s[start];
			i++;
			start++;
		}
		p[i] = '\0';
	}
	return (p);
}
