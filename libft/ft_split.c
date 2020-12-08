/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:29:16 by abel-mak          #+#    #+#             */
/*   Updated: 2019/11/13 14:38:20 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		numtokens(int len, char const *s, char c)
{
	int i;
	int res;

	res = 0;
	i = 1;
	while (i <= len)
	{
		if ((s[i] == '\0' || s[i] == c) &&
				(s[i - 1] != '\0' && s[i - 1] != c))
		{
			res++;
		}
		i++;
	}
	return (res);
}

static char		*fill(char const *s, char c)
{
	int		i;
	char	*p;
	int		tokenlen;

	tokenlen = 0;
	while (s[tokenlen] != c && s[tokenlen] != '\0')
		tokenlen++;
	i = 0;
	p = (char*)malloc(sizeof(char) * (tokenlen + 1));
	if (p == NULL)
		return (NULL);
	while ((s[i] != '\0' && s[i] != c))
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char		**arr_free(char **p, int i)
{
	i = i - 1;
	while (i >= 0)
	{
		free(p[i]);
		i--;
	}
	free(p);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	p = (char**)malloc(sizeof(char*) * (numtokens(ft_strlen(s), s, c) + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < numtokens(ft_strlen(s), s, c))
	{
		while (s[j] == c && (size_t)j < ft_strlen(s))
			j++;
		p[i] = fill(s + j, c);
		if (p[i] == NULL)
			return (arr_free(p, i));
		while (s[j] != c && (size_t)j < ft_strlen(s))
			j++;
		i++;
	}
	p[i] = NULL;
	return (p);
}
