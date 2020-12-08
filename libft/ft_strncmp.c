/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:20:09 by abel-mak          #+#    #+#             */
/*   Updated: 2019/11/06 15:04:22 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n != 0)
	{
		while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
		{
			if (s1[i] != s2[i])
			{
				return (((unsigned char)s1[i] - (unsigned char)s2[i]));
			}
			i++;
		}
	}
	return (0);
}
