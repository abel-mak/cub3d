/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:46:49 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/18 09:07:42 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

/*
** ready variable is to check all elements are set before
** reading the map otherwise return error
** 255 is just 1 << 7 | 1 << 6 | 1 << 5.. | 1
** 511 is just 1 << 8 | 1 << 7 |... | 1
** any value different from 255 or 511 return error
*/

int		check_invalid(char *line)
{
	while (*line != '\0')
	{
		if (*line != ' ')
			return (1);
		line++;
	}
	return (0);
}

/*
** check_if_set will check if variable is set
** if it's set return error because it will reset
** to another variable => another malloc => leak
*/

int		is_set(t_file *cub_file, int nbit)
{
	if (((cub_file->ready >> nbit) & 1) == 1)
	{
		put_error("duplicate element");
		exit(0);
	}
	return (1);
}

void	get_elem(t_file *c, char *line)
{
	if (line[0] == 'R' && line[1] == ' ' && is_set(c, 0))
		c->ready |= (get_r(c, line + 1));
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ' && is_set(c, 1))
		c->ready |= get_path(&(c->no), line + 2) << 1;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ' && is_set(c, 2))
		c->ready |= get_path(&(c->so), line + 2) << 2;
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ' && is_set(c, 3))
		c->ready |= get_path(&(c->we), line + 2) << 3;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ' && is_set(c, 4))
		c->ready |= get_path(&(c->ea), line + 2) << 4;
	else if (line[0] == 'S' && line[1] == '1' && line[2] == ' ' && is_set(c, 5))
		c->ready |= get_path(&(c->s1), line + 2) << 5;
	else if (line[0] == 'S' && line[1] == '2' && line[2] == ' ' && is_set(c, 8))
		c->ready |= get_path(&(c->s2), line + 2) << 8;
	else if (line[0] == 'F' && line[1] == ' ' && is_set(c, 6))
		c->ready |= color(&(c->f), line + 1, "F") << 6;
	else if (line[0] == 'C' && line[1] == ' ' && is_set(c, 7))
		c->ready |= color(&(c->c), line + 1, "C") << 7;
	else if (start_map(line) == 1 && is_set(c, 9) && (c->ready == 255
				|| c->ready == 511))
		c->ready |= get_map(c, line) << 9;
	else if (line[0] == 'S' && line[1] == ' ' && is_set(c, 5))
		c->ready |= get_path(&(c->s1), line + 2) << 5;
	else if (check_invalid(line) == 1)
		put_error("invalid charater or missing element");
}

int		is_second_sp(t_file *c)
{
	int i;
	int j;

	i = 0;
	while (i < c->map_h)
	{
		j = 0;
		while (j < c->map_w)
		{
			if (c->map[i][j] == '3')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_file	*parse(char **argv)
{
	char	*line;
	int		r;
	t_file	*cub_file;

	cub_file = malloc(sizeof(t_file));
	cub_file->fd = open(argv[1], O_RDONLY);
	if (cub_file->fd == -1)
		put_error("file doesn't exist");
	cub_file->ready = 0;
	r = 1;
	while (r == 1)
	{
		r = get_next_line(cub_file->fd, &line);
		get_elem(cub_file, line);
		free(line);
	}
	if (cub_file->ready != 1023 && cub_file->ready != 767)
		put_error("missing elements");
	if (((cub_file->ready >> 8) & 1) == 0 && is_second_sp(cub_file) == 1)
		put_error("there is no second sprite path and you put it on the map");
	return (cub_file);
}
