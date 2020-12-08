/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:44:11 by abel-mak          #+#    #+#             */
/*   Updated: 2019/11/06 15:48:30 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dst1;
	char		*src1;

	if (dst == src)
		return (dst);
	src1 = (char*)src;
	dst1 = dst;
	i = 0;
	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}
