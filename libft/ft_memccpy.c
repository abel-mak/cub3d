/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:36:55 by abel-mak          #+#    #+#             */
/*   Updated: 2019/10/28 16:24:32 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == ((unsigned char*)src)[i])
		{
			((unsigned char*)dst)[i] = (unsigned char)c;
			return (dst + i + 1);
		}
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (NULL);
}
