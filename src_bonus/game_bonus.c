/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:44:42 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 09:53:07 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

/*
** destroy old image and get new image
*/

void	get_new_image(t_data *info)
{
	mlx_destroy_image(info->mlx_ptr, info->img_ptr);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	info->img_ptr = mlx_new_image(info->mlx_ptr,
			info->cub_file->w_width, info->cub_file->w_height);
	info->data = (int*)mlx_get_data_addr(info->img_ptr,
			&(info->bits_per_pixel), &(info->size_line), &(info->endian));
}

void	build_image(t_data *info, int key)
{
	castwalls(info);
	if (key == SPACE)
		update_gun(key, info);
	else
		draw_gun(info, 0);
	if (info->cub_file->w_width >= 300 && info->cub_file->w_height >= 300)
	{
		draw_map(info);
		castrays(info);
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
	if (info->animation->frames >= 7)
		clear_gun(key, info);
}

/*
** polaire cords
** for up and down player(+=r*cos(@), +=r*sin(@)) => teta
** for left and right player(+=r*sin(@), +=-rcos(@)) => phi
*/

int		update(int key, t_data *info)
{
	float xcord;
	float ycord;

	xcord = cos(info->player->rotangle) * (BO / 3);
	ycord = sin(info->player->rotangle) * (BO / 3);
	get_new_image(info);
	if (key == LEFT)
		info->player->rotangle -= 0.1;
	else if (key == RIGHT)
		info->player->rotangle += 0.1;
	else if (key == WKEY)
		check_next_pos_up(info, xcord, ycord);
	else if (key == SKEY)
		check_next_pos_up(info, -xcord, -ycord);
	else if (key == AKEY)
		check_next_pos_up(info, ycord, -xcord);
	else if (key == DKEY)
		check_next_pos_up(info, -ycord, xcord);
	else if (key == ENTER)
		info->dark = (info->dark == 0) ? 1 : 0;
	else if (key == 53)
		free_exit(info);
	build_image(info, key);
	return (1);
}

int		keyrelease(int key, t_data *info)
{
	t_file *c;

	(void)key;
	c = info->cub_file;
	mlx_destroy_image(info->mlx_ptr, info->img_ptr);
	info->img_ptr = mlx_new_image(info->mlx_ptr, c->w_width, c->w_height);
	info->data = (int*)mlx_get_data_addr(info->img_ptr, &(info->bits_per_pixel)
			, &(info->size_line), &(info->endian));
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	castwalls(info);
	draw_gun(info, 0);
	info->animation->frames = 0;
	if (info->cub_file->w_width >= 300 && info->cub_file->w_height >= 300)
	{
		draw_map(info);
		castrays(info);
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
	return (0);
}

/*
** from X11.h
** Keypress event 2
** Keyrelease event 3
** Destroy Notify event 17 (for closing window from red cross)
*/

void	game_loop(t_data *info)
{
	mlx_hook(info->win_ptr, 2, 0, update, info);
	mlx_hook(info->win_ptr, 3, 0, keyrelease, info);
	mlx_hook(info->win_ptr, 17, 0, free_exit, info);
	mlx_loop(info->mlx_ptr);
}
