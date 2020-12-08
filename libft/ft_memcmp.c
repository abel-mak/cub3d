/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:28:29 by abel-mak          #+#    #+#             */
/*   Updated: 2019/10/29 18:10:50 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_;
	unsigned char	*s2_;

	s2_ = (unsigned char*)s2;
	s1_ = (unsigned char*)s1;
	i = 0;
	while (i < n)
	{
		if (s1_[i] != s2_[i])
		{
			return (s1_[i] - s2_[i]);
		}
		i++;
	}
	return (0);
}
