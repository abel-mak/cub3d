/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:25:24 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/18 08:51:43 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int		scale_gun_w(t_file *c)
{
	int res;

	res = (c->w_width * 3 / 800);
	if (res > 3)
		res = 3;
	return (res);
}

int		scale_gun_h(t_file *c)
{
	int res;

	res = (c->w_height * 3 / 800);
	if (res > 3)
		res = 3;
	return (res);
}

void	draw_gun(t_data *info, int n)
{
	int		x;
	int		tmp_x;
	int		y;
	int		color;
	t_file	*c;

	c = info->cub_file;
	x = 0;
	tmp_x = n * info->animation->w * scale_gun_w(c);
	while (x < info->animation->w * scale_gun_w(c))
	{
		y = 0;
		while (y < info->animation->h * scale_gun_h(c))
		{
			color = info->animation->data
				[(y / scale_gun_h(c)) * 614 + (tmp_x / scale_gun_w(c))];
			if (color != -16777216 && color != 9129261)
				info->data
					[(y + (c->w_height - info->animation->h * scale_gun_h(c)))
						* c->w_width + (x + (c->w_width / 2))] = color;
			y++;
		}
		tmp_x++;
		x++;
	}
}

/*
** clear the gun if user keep pressing
*/

int		clear_gun(int key, t_data *info)
{
	int x;
	int tmp_x;

	(void)key;
	x = 0;
	tmp_x = 0;
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	castwalls(info);
	draw_gun(info, 0);
	if (info->cub_file->w_width >= 300 && info->cub_file->w_height >= 300)
	{
		draw_map(info);
		castrays(info);
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
	return (0);
}

/*
** before update_gun i first clear the window(map + castwall + first frame gun)
** then castwall will fill image with walls after that
** update_gun will draw into that image
** the gun starting from the second frame (info->animation->n > 0)
*/

int		update_gun(int key, t_data *info)
{
	t_file *c;

	(void)key;
	c = info->cub_file;
	while (info->animation->n < 6)
	{
		if (info->animation->n > 0)
			draw_gun(info, info->animation->n);
		info->animation->n++;
		info->animation->frames++;
	}
	if (info->animation->n == 6)
		info->animation->n = 0;
	return (0);
}
