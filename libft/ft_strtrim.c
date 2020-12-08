/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:27:00 by abel-mak          #+#    #+#             */
/*   Updated: 2020/10/20 10:25:27 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check(char const *set, int c)
{
	int i;

	i = 0;
	if (set == NULL)
		return (0);
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/*
**find first and last indices return first and last
** res[0] index of first string trimed, res[1] last one
** (res[0] + res[1] + 1) is length of string
*/

static int		*firstlast(char const *s1, char const *set, int *res)
{
	int first;
	int last;

	last = ft_strlen(s1) - 1;
	first = 0;
	while (check(set, s1[first]) == 1)
	{
		first++;
	}
	while (check(set, s1[last]) == 1 && (size_t)first != ft_strlen(s1))
	{
		last--;
	}
	if ((size_t)first == ft_strlen(s1))
		first = last + 1;
	res[0] = first;
	res[1] = last;
	return (res);
}

/*
** if first == length of s1, then set first = last + 1
** so that allocate one character and never enter the while loop in ft_strtrim
*/

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*p;
	int		res[2];

	if (s1 == NULL)
	{
		return (NULL);
	}
	firstlast(s1, set, res);
	p = (char*)malloc(sizeof(char) * (res[1] - res[0] + 1) + 1);
	if (p == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < (res[1] - res[0] + 1))
	{
		p[i] = s1[res[0] + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
