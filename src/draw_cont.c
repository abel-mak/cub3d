/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cont.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:37:32 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/18 09:17:00 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_sprite_stripe(t_data *info, t_sprite *sp, float raydist, int i)
{
	float	tmp;
	t_point	tex;
	int		color;
	t_file	*c;

	c = info->cub_file;
	tmp = c->w_height / 2 - sp->sprite_height / 2;
	while (sp->start < c->w_width
			&& tmp < c->w_height / 2 + sp->sprite_height / 2 &&
			sp->dist_to_p < raydist /
			cosf(atanf((i - (c->w_width / 2)) / info->dplane)))
	{
		tex.x = (sp->start - (sp->xposition -
					(sp->hei_off) / 2)) * (64 / (sp->hei_off));
		tex.y = (tmp -
			(c->w_height / 2 - (sp->hei_off) / 2)) * (64 / (sp->hei_off));
		color = info->spritedata[sp->code][((int)tex.y * 64 + (int)tex.x)];
		if (color != -16777216 && tex.y < 64 && tex.x < 64)
			info->data[(int)tmp * c->w_width + (int)sp->start] = darken(info,
					info->spritedata[sp->code][(int)tex.y * 64 + (int)tex.x],
					sp->sprite_height,
					c->w_height);
		tmp++;
	}
}

void	sprite_draw(t_data *info, int i, float raydist)
{
	t_sprite	**spt;
	int			ind;

	ind = 0;
	spt = sprite_sort(info);
	while (ind < info->num_spr)
	{
		if (i > spt[ind]->start && spt[ind]->start < spt[ind]->end
				&& spt[ind]->visible == 1)
		{
			draw_sprite_stripe(info, spt[ind], raydist, i);
			spt[ind]->start++;
		}
		ind++;
	}
}

float	get_wall(t_data *info, t_ray *ray, t_wall *wall, int i)
{
	float wallheight;

	wallheight = 0;
	wall->offset = 0;
	ray->hitverti = 0;
	ray->horiz = horizint(info->player, info->cub_file, normalize(ray->angle));
	ray->verti = verticint(info->player, info->cub_file, normalize(ray->angle));
	if (dist(ray->horiz, info->player->pos) >
			dist(ray->verti, info->player->pos))
	{
		ray->raydist = dist(ray->verti, info->player->pos)
			* cosf(atanf((i - (info->cub_file->w_width / 2)) / info->dplane));
		ray->hitverti = 1;
	}
	else
		ray->raydist = dist(ray->horiz, info->player->pos)
			* cosf(atanf((i - (info->cub_file->w_width / 2)) / info->dplane));
	wallheight = (BO / ray->raydist) * info->dplane;
	if (wallheight > info->cub_file->w_height)
	{
		wall->offset = (wallheight - info->cub_file->w_height);
		wallheight = info->cub_file->w_height;
	}
	wall->hei_off = wallheight + wall->offset;
	return (wallheight);
}

/*
** darken will make a pixel color  more darken
** based on a coefficient smaler than one 1
** that we get from value and max value
*/

int		darken(t_data *info, int color, float value, float max_value)
{
	float coef;

	max_value = (max_value == 0) ? 1 : max_value;
	coef = value / max_value;
	coef = (coef > 1) ? 1 : coef;
	if (info->dark == 0)
		coef = 1;
	return (rgb(((color & 0x00FF0000) >> 16) * coef,
				((color & 0x0000FF00) >> 8) * coef,
				(color & 0x000000FF) * coef));
}
