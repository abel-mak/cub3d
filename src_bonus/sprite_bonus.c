/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:49:11 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 09:49:54 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void		reset_sprite(t_data *info, t_sprite *sp)
{
	t_player *player;

	player = info->player;
	sp->offset = 0;
	sp->visible = 0;
	sp->angle = minuspitopi(atan2f(sp->pos->y - player->pos->y,
				sp->pos->x - player->pos->x) - player->rotangle);
	sp->dist_to_p = dist(player->pos, sp->pos);
	sp->sprite_height = (info->dplane * BO) / sp->dist_to_p;
	if (sp->sprite_height > info->cub_file->w_height)
	{
		sp->offset = sp->sprite_height - info->cub_file->w_height;
		sp->sprite_height = info->cub_file->w_height;
	}
	sp->hei_off = sp->sprite_height + sp->offset;
}

void		sprite_update(t_data *info)
{
	t_sprite	**spt;
	t_player	*player;
	int			ind;

	ind = 0;
	spt = info->spt;
	player = info->player;
	while (ind < info->num_spr)
	{
		reset_sprite(info, spt[ind]);
		if (spt[ind]->angle >= (float)(-50 * PI / 180)
				&& spt[ind]->angle <= (float)(50 * PI / 180))
		{
			spt[ind]->xposition = info->cub_file->w_width / 2 +
				(tan(spt[ind]->angle) * info->dplane);
			spt[ind]->start = spt[ind]->xposition - spt[ind]->sprite_height / 2;
			spt[ind]->end = spt[ind]->xposition + spt[ind]->sprite_height / 2;
			spt[ind]->visible = 1;
		}
		if (info->spt[ind]->start < 0)
			info->spt[ind]->start = 0;
		ind++;
	}
}

t_sprite	**sprite_sort(t_data *info)
{
	t_sprite	**spt;
	t_sprite	*tmp;
	int			i;

	spt = info->spt;
	i = 1;
	while (i < info->num_spr)
	{
		if (spt[i - 1]->dist_to_p < spt[i]->dist_to_p)
		{
			tmp = spt[i - 1];
			spt[i - 1] = spt[i];
			spt[i] = tmp;
			i = 0;
		}
		i++;
	}
	return (spt);
}
