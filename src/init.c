/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:16:07 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/15 11:57:28 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_data	*init_info(char **argv)
{
	t_file *cub_file;
	t_data *info;

	cub_file = parse(argv);
	info = malloc(sizeof(t_data));
	info->cub_file = cub_file;
	info->dplane = (info->cub_file->w_width / 2) / tanf(FOV / 2);
	info->mlx_ptr = mlx_init();
	info->win_ptr = mlx_new_window(info->mlx_ptr, info->cub_file->w_width,
			info->cub_file->w_height, "cub3d");
	info->animation = init_animation(info);
	info->player = malloc(sizeof(t_player));
	info->player->pos = (t_point*)malloc(sizeof(t_point));
	info->player->pos->x = 0;
	info->player->pos->y = 0;
	info->player->rotangle = (float)0;
	info->map = cub_file->map;
	info->img_ptr = mlx_new_image(info->mlx_ptr, info->cub_file->w_width,
			info->cub_file->w_height);
	info->data = (int*)mlx_get_data_addr(info->img_ptr, &(info->bits_per_pixel),
			&(info->size_line), &(info->endian));
	initplayer(info);
	info->spt = init_sprites(info->num_spr);
	init_sprites_pos(info);
	return (info);
}

void	init_wall_tex(t_data *info)
{
	void	*texptr[4];
	int		w;
	int		h;
	t_file	*c;

	c = info->cub_file;
	texptr[0] = mlx_xpm_file_to_image(info->mlx_ptr, c->we, &w, &h);
	texptr[1] = mlx_xpm_file_to_image(info->mlx_ptr, c->so, &w, &h);
	texptr[2] = mlx_xpm_file_to_image(info->mlx_ptr, c->ea, &w, &h);
	texptr[3] = mlx_xpm_file_to_image(info->mlx_ptr, c->no, &w, &h);
	info->textdata = (int**)malloc(sizeof(int*) * 4);
	info->textdata[0] = (int*)mlx_get_data_addr(texptr[0]
			, &(info->bits_per_pixel), &(info->size_line), &(info->endian));
	info->textdata[1] = (int*)mlx_get_data_addr(texptr[1]
			, &(info->bits_per_pixel), &(info->size_line), &(info->endian));
	info->textdata[2] = (int*)mlx_get_data_addr(texptr[2],
			&(info->bits_per_pixel), &(info->size_line), &(info->endian));
	info->textdata[3] = (int*)mlx_get_data_addr(texptr[3],
			&(info->bits_per_pixel), &(info->size_line), &(info->endian));
}

void	init_sp_tex(t_data *info)
{
	void	*sptexptr[2];
	t_file	*c;

	c = info->cub_file;
	info->spritedata = (int**)malloc(sizeof(int*) * 2);
	if (info->num_spr > 0)
	{
		sptexptr[0] = mlx_xpm_file_to_image(info->mlx_ptr,
				c->s1, &info->spt[0]->width, &info->spt[0]->height);
		info->spritedata[0] = (int*)mlx_get_data_addr(sptexptr[0],
				&info->bits_per_pixel, &info->size_line, &info->endian);
		if (((c->ready >> 8) & 1) == 0)
			c->s2 = c->s1;
		sptexptr[1] = mlx_xpm_file_to_image(info->mlx_ptr,
				c->s2, &info->spt[0]->width, &info->spt[0]->height);
		info->spritedata[1] = (int*)mlx_get_data_addr(sptexptr[1],
				&info->bits_per_pixel, &info->size_line, &info->endian);
	}
}

void	initplayer(t_data *info)
{
	int		i;
	int		j;
	t_point box;

	info->num_spr = 0;
	i = 0;
	while (i < info->cub_file->map_h)
	{
		j = 0;
		while (j < info->cub_file->map_w)
		{
			box.x = BO * j;
			box.y = BO * i;
			if (is_pos(info->map[i][j]) == 1)
			{
				info->player->pos->x = box.x + ((float)BO) / 2;
				info->player->pos->y = box.y + ((float)BO) / 2;
				set_player_rotangle(info, i, j);
			}
			else if (info->map[i][j] == '2' || info->map[i][j] == '3')
				info->num_spr++;
			j++;
		}
		i++;
	}
}

void	init_sprites_pos(t_data *info)
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
			if (info->map[i][j] == '2' || info->map[i][j] == '3')
			{
				info->spt[ind]->pos->x = (j * BO) + BO / 2;
				info->spt[ind]->pos->y = (i * BO) + BO / 2;
				info->spt[ind]->code = info->map[i][j] - '2';
				ind++;
			}
			j++;
		}
		i++;
	}
}
