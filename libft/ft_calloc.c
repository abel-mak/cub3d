/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:13:15 by abel-mak          #+#    #+#             */
/*   Updated: 2019/10/31 17:26:05 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
