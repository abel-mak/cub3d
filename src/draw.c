/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:34:02 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/18 09:16:41 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_ceil_strip(t_data *info, int column, float wallheight)
{
	int		from;
	int		end;
	t_file	*c;

	c = info->cub_file;
	from = 0;
	end = (int)floorf((c->w_height / 2) - (wallheight / 2));
	while (from < end)
	{
		info->data[from * c->w_width + column] =
			darken(info, c->c,
					fabsf((float)(from + c->w_height / 4) - (c->w_height)),
					c->w_height);
		from++;
	}
}

void	draw_floor_strip(t_data *info, int column, float wallheight)
{
	int		from;
	int		end;
	t_file	*c;

	c = info->cub_file;
	from = c->w_height / 2 + wallheight / 2;
	end = c->w_height;
	while (from < end)
	{
		info->data[from * c->w_width + column] =
			darken(info, c->f,
					(float)(from + (float)(c->w_height / 30)),
					c->w_height);
		from++;
	}
}

float	get_tex_y(int from, t_file *c, t_wall *wall)
{
	return ((from - ((c->w_height / 2)
					- ((wall->hei_off) / 2))) * (64 / (wall->hei_off)));
}

void	draw_wall_strip(t_data *info, int column, t_wall *wall, t_ray *ray)
{
	int		from;
	t_file	*c;
	t_point	tex;

	c = info->cub_file;
	from = floorf((c->w_height / 2) - (wall->height / 2));
	tex.x = (ray->hitverti == 1) ? fmod(ray->verti->y, 64) :
		fmodf(ray->horiz->x, 64);
	while (from < floorf((c->w_height / 2) + (wall->height / 2)))
	{
		tex.y = get_tex_y(from, c, wall);
		if (ray->hitverti == 1 && israyright(normalize(ray->angle)) == 0)
			info->data[from * c->w_width + column] = darken(info, info->textdata
				[0][((int)tex.y * 64 + (int)tex.x)], wall->height, c->w_height);
		else if (ray->hitverti == 0 && israydown(normalize(ray->angle)) == 1)
			info->data[from * c->w_width + column] = darken(info, info->textdata
				[1][((int)tex.y * 64 + (int)tex.x)], wall->height, c->w_height);
		else if (ray->hitverti == 1 && israyright(normalize(ray->angle) == 1))
			info->data[from * c->w_width + column] = darken(info, info->textdata
				[2][((int)tex.y * 64 + (int)tex.x)], wall->height, c->w_height);
		else if (ray->hitverti == 0 && israydown(normalize(ray->angle)) == 0)
			info->data[from * c->w_width + column] = darken(info, info->textdata
				[3][((int)tex.y * 64 + (int)tex.x)], wall->height, c->w_height);
		from++;
	}
}

void	castwalls(t_data *info)
{
	t_player	*player;
	float		end_angle;
	t_wall		wall;
	int			i;
	t_ray		ray;

	i = 0;
	player = info->player;
	ray.angle = player->rotangle - FOV / 2;
	end_angle = player->rotangle + FOV / 2;
	wall.height = 0;
	sprite_update(info);
	while (ray.angle < end_angle && i < info->cub_file->w_width)
	{
		ray.angle = player->rotangle +
			atan((i - (info->cub_file->w_width / 2)) / info->dplane);
		wall.height = get_wall(info, &ray, &wall, i);
		draw_ceil_strip(info, i, wall.height);
		draw_wall_strip(info, i, &wall, &ray);
		draw_floor_strip(info, i, wall.height);
		sprite_draw(info, i, ray.raydist);
		free(ray.horiz);
		free(ray.verti);
		i++;
	}
}
