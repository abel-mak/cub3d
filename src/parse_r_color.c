/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_r_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:46:06 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 10:28:54 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int		set_res(int *res, int *j)
{
	int i;

	i = 0;
	while (i < 3)
	{
		res[i] = -1;
		i++;
	}
	*j = 0;
	return (1);
}

int		check_res(int *res, int j)
{
	if (j < 2 || (res[0] < 0 || res[1] < 0 || res[2] < 0)
		|| (res[0] > 255 || res[1] > 255 || res[2] > 255))
		return (1);
	return (0);
}

int		color(int *col, char *str, char *code)
{
	int j;
	int res[3];

	while ((set_res(&res[0], &j)) && (*str == ' ' && *str != '\0') && str++)
		;
	res[j++] = (ft_isdigit(*str) == 1) ? ft_atoi(str) : put_error(code);
	while (j < 3 && (ft_isdigit(*str) || *str == ',' || *str == ' '))
	{
		if (*str == ',')
		{
			str++;
			while (*str == ' ' && str++)
				;
			res[j++] = ft_atoi(str);
		}
		while (((ft_isdigit(*str) == 1) || (*str == ' ' && j < 3)) && str++)
			;
	}
	while (*str != '\0')
		if (*(str++) != ' ')
			put_error(code);
	if (check_res(&res[0], j) == 1)
		put_error(code);
	*col = (res[0] << 16) + (res[1] << 8) + res[2];
	return (1);
}

int		get_r(t_file *cub_file, char *line)
{
	while (*(line) == ' ' && line++)
		;
	cub_file->w_width = ft_atoi(line);
	while (ft_isdigit(*(line)) != 0 && line++)
		;
	cub_file->w_height = ft_atoi(line);
	if (cub_file->w_width <= 0 || cub_file->w_height <= 0)
		put_error("wrong resolution");
	if (cub_file->w_width > 2560)
		cub_file->w_width = 2560;
	if (cub_file->w_height > 1440)
		cub_file->w_height = 1440;
	while (*(line) == ' ' && line++)
		;
	while (ft_isdigit(*(line)) != 0 && line++)
		;
	while (*line != '\0')
	{
		if (*(line) != ' ')
			put_error("wrong resolution");
		line++;
	}
	check_resolution(cub_file);
	return (1);
}

void	check_resolution(t_file *c)
{
	if (c->w_width < 2)
		c->w_width = 2;
	if (c->w_height < 2)
		c->w_height = 2;
}
