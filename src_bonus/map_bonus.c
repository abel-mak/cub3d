/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:46:10 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 09:52:01 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	draw_rect_map(t_data *info, int i, int j)
{
	float	box_size;
	t_point	box;

	box_size = 8;
	box.x = j * box_size;
	box.y = i * box_size;
	if (info->map[i][j] == '1')
	{
		rect(info, pnt(box.x - info->trans_x, box.y - info->trans_y),
				box_size, rgb(255, 0, 0));
	}
	else if (info->map[i][j] == '2')
		rect(info, pnt(box.x - info->trans_x, box.y - info->trans_y),
				box_size, rgb(50, 250, 0));
	else if (info->map[i][j] == '3')
		rect(info, pnt(box.x - info->trans_x, box.y - info->trans_y),
				box_size, rgb(165, 42, 42));
}

void	draw_map(t_data *info)
{
	int i;
	int j;
	int ind;

	ind = 0;
	i = 0;
	while (i < info->cub_file->map_h)
	{
		j = 0;
		while (j < info->cub_file->map_w)
		{
			if (is_by_player(info, i, j))
			{
				info->trans_x = ((info->player->pos->x / BO) - 10) > 0 ?
					((info->player->pos->x / BO) - 10) * 8 : 0;
				info->trans_y = ((info->player->pos->y / BO) - 10) > 0 ?
					((info->player->pos->y / BO) - 10) * 8 : 0;
				draw_rect_map(info, i, j);
			}
			j++;
		}
		i++;
	}
}

t_point	*horizint(t_player *player, t_file *cub_file, float normangle)
{
	t_point *horiz;
	float	hxstep;
	float	hystep;
	float	tmphorizy;

	horiz = (t_point*)malloc(sizeof(t_point));
	horiz->y = (int)(player->pos->y / BO) * BO;
	horiz->y += (israydown(normangle) == 1) ? BO : 0;
	horiz->x = player->pos->x + ((horiz->y - player->pos->y) / tanf(normangle));
	hystep = BO;
	hxstep = fabsf(hystep / tanf(normangle));
	hystep *= (israydown(normangle) == 1) ? 1 : -1;
	hxstep *= (israyright(normangle) == 1) ? 1 : -1;
	while (horiz->x > 0 && horiz->x < cub_file->map_w * BO && horiz->y > 0
			&& horiz->y < cub_file->map_h * BO)
	{
		tmphorizy = (israydown(normangle) == 0) ? horiz->y - 1 : horiz->y;
		if (cub_file->map[(int)(tmphorizy / BO)]
				[(int)(horiz->x / BO)] == '1')
			break ;
		horiz->x += hxstep;
		horiz->y += hystep;
	}
	return (horiz);
}

t_point	*verticint(t_player *player, t_file *cub_file, float normangle)
{
	t_point	*verti;
	float	vxstep;
	float	vystep;
	float	tmpvertix;

	verti = (t_point*)malloc(sizeof(t_point));
	verti->x = (int)(player->pos->x / BO) * BO;
	verti->x += (israyright(normangle) == 1) ? BO : 0;
	verti->y = player->pos->y + tanf(normangle) * (verti->x - player->pos->x);
	vxstep = BO;
	vystep = fabsf(vxstep * tanf(normangle));
	vxstep *= (israyright(normangle) == 1) ? 1 : -1;
	vystep *= (israydown(normangle) == 1) ? 1 : -1;
	while (verti->x > 0 && verti->x < cub_file->map_w * BO && verti->y > 0
			&& verti->y < cub_file->map_h * BO)
	{
		tmpvertix = (israyright(normangle) == 0) ? verti->x - 1 : verti->x;
		if (cub_file->map[(int)(verti->y / BO)]
				[(int)(tmpvertix / BO)] == '1')
			break ;
		verti->x += vxstep;
		verti->y += vystep;
	}
	return (verti);
}

void	castrays(t_data *info)
{
	t_point		*horiz;
	t_point		*verti;
	t_player	*player;
	t_angle		angle;

	player = info->player;
	angle.start = player->rotangle - FOV / 2;
	angle.end = player->rotangle + FOV / 2;
	while (angle.start < angle.end)
	{
		horiz = horizint(info->player, info->cub_file, normalize(angle.start));
		verti = verticint(info->player, info->cub_file, normalize(angle.start));
		angle.start += FOV / 30;
		if (dist(horiz, player->pos) > dist(verti, player->pos)
				&& is_by_player(info, verti->y / BO, verti->x / BO))
			line(info, pnt((player->pos->x / BO) * 8 - info->trans_x,
			(player->pos->y / BO) * 8 - info->trans_y), pnt((verti->x / BO) * 8
			- info->trans_x, (verti->y / BO) * 8 - info->trans_y));
		else if (is_by_player(info, horiz->y / BO, horiz->x / BO))
			line(info, pnt((player->pos->x / BO) * 8 - info->trans_x,
			(player->pos->y / BO) * 8 - info->trans_y), pnt((horiz->x / BO) * 8
			- info->trans_x, (horiz->y / BO) * 8 - info->trans_y));
		free(horiz);
		free(verti);
	}
}
