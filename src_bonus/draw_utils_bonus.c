/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:44:17 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 09:53:28 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int		rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((int)(r * pow(256, 2) + g * pow(256, 1) + b));
}

void	data_pixel_put(t_data *info, int x, int y, int color)
{
	info->data[y * info->cub_file->w_width + x] = color;
}

void	line_verti(t_data *info, t_point *p1, t_point *p2)
{
	if (p1->y > p2->y)
		swap(&(p1->y), &(p2->y));
	while (p1->y < p2->y)
	{
		data_pixel_put(info, p1->x, p1->y, rgb(0, 0, 0));
		p1->y++;
	}
}

void	line(t_data *info, t_point *p1, t_point *p2)
{
	float a;
	float b;
	float y;

	if (p1->x != p2->x)
	{
		a = (p2->y - p1->y) / (p2->x - p1->x);
		b = p1->y - a * p1->x;
		if (p1->x > p2->x)
			swap(&(p1->x), &(p2->x));
		while (p1->x < p2->x)
		{
			y = a * p1->x + b;
			data_pixel_put(info, p1->x, y, rgb(0, 0, 0));
			p1->x++;
		}
	}
	else
		line_verti(info, p1, p2);
	free(p1);
	free(p2);
}

void	rect(t_data *info, t_point *p, float size, int color)
{
	int i;
	int j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			data_pixel_put(info, (p->x + i), (p->y + j), color);
			i++;
		}
		j++;
	}
	free(p);
}
