/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cont_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:45:31 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 09:52:24 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

t_sprite	**init_sprites(int num_spr)
{
	int			i;
	t_sprite	**sprites_table;

	sprites_table = (t_sprite**)malloc(sizeof(t_sprite*) * num_spr);
	i = 0;
	while (i < num_spr)
	{
		sprites_table[i] = (t_sprite*)malloc(sizeof(t_sprite));
		sprites_table[i]->pos = (t_point*)malloc(sizeof(t_point));
		i++;
	}
	return (sprites_table);
}

t_animation	*init_animation(t_data *info)
{
	t_animation	*animation;
	int			width;
	int			height;

	animation = (t_animation*)malloc(sizeof(t_animation));
	animation->img_ptr = mlx_xpm_file_to_image(info->mlx_ptr,
			"./textures/gun.xpm", &width, &height);
	animation->data = (int*)mlx_get_data_addr(animation->img_ptr
			, &(info->bits_per_pixel), &(info->size_line), &(info->endian));
	animation->w = 94;
	animation->h = 131;
	animation->n = 0;
	animation->frames = 0;
	return (animation);
}
