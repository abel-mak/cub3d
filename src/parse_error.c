/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:48:17 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/10 13:54:07 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int		put_error(char *code)
{
	write(1, ERO, ft_strlen(ERO));
	write(1, code, ft_strlen(code));
	write(1, "\n", 1);
	exit(0);
	return (-1);
}

void	map_error(int i, int j)
{
	char *istr;
	char *jstr;

	istr = ft_itoa(i);
	jstr = ft_itoa(j);
	write(1, ERO, ft_strlen(ERO));
	write(1, " map ", ft_strlen(" map "));
	write(1, istr, ft_strlen(istr));
	write(1, ", ", 2);
	write(1, jstr, ft_strlen(jstr));
	write(1, "\n", 1);
	exit(0);
}

/*
** inner navigetion sprites(2, 3)
*/

int		is_inner(char c)
{
	char *inner;

	inner = "023NSEW";
	if (ft_strchr(inner, c) != NULL)
		return (1);
	return (0);
}

void	check_space_neighbors(char **arr, int i, int j, t_file *c)
{
	int h;
	int w;

	w = c->map_w;
	h = c->map_h;
	if ((i + 1 < h && is_inner(arr[i + 1][j]) == 1))
		map_error(i + 1, j);
	else if (i - 1 >= 0 && is_inner(arr[i - 1][j]) == 1)
		map_error(i - 1, j);
	else if (j + 1 < w && is_inner(arr[i][j + 1]) == 1)
		map_error(i, j + 1);
	else if (j - 1 >= 0 && is_inner(arr[i][j - 1]) == 1)
		map_error(i, j - 1);
	else if (i + 1 < h && j + 1 < w && is_inner(arr[i + 1][j + 1]) == 1)
		map_error(i + 1, j + 1);
	else if (i - 1 >= 0 && j - 1 >= 0 && is_inner(arr[i - 1][j - 1]) == 1)
		map_error(i - 1, j - 1);
	else if (i - 1 >= 0 && j + 1 < w && is_inner(arr[i - 1][j + 1]) == 1)
		map_error(i - 1, j + 1);
	else if (i + 1 < h && j - 1 >= 0 && is_inner(arr[i + 1][j - 1]) == 1)
		map_error(i + 1, j - 1);
}

int		check_c(char **arr, t_file *c)
{
	int i;
	int j;
	int nav;

	nav = 0;
	i = 0;
	while (i < c->map_h)
	{
		j = 0;
		while (j < c->map_w)
		{
			if (arr[i][j] != '0'
					&& arr[i][j] != '2' && arr[i][j] != '3'
					&& is_inner(arr[i][j]) == 1)
				nav++;
			else if (arr[i][j] == ' ')
				check_space_neighbors(arr, i, j, c);
			j++;
		}
		i++;
	}
	if (nav != 1)
		put_error("5: wrong navigation\n");
	return (0);
}
