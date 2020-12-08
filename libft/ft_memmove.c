/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:23:50 by abel-mak          #+#    #+#             */
/*   Updated: 2019/11/06 16:05:54 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if ((char*)dst > (char*)src && len != 0)
	{
		i = len - 1;
		while ((long long)i >= 0)
		{
			((char*)dst)[i] = ((char*)src)[i];
			i--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
