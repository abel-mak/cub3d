/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:49:47 by abel-mak          #+#    #+#             */
/*   Updated: 2019/11/06 19:25:45 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	if (haystack == NULL && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char*)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j]
		&& (haystack[i + j] != '\0' && needle[j] != '\0')
		&& j + i < len)
		{
			j++;
		}
		if (j == ft_strlen(needle))
		{
			return ((char*)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
