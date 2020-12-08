/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:09:39 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/18 08:52:59 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	free_cub_file(t_file *c)
{
	int i;

	i = 0;
	while (i < c->map_h)
	{
		free(c->map[i]);
		i++;
	}
	free(c->map);
	free(c->no);
	free(c->so);
	free(c->we);
	free(c->ea);
	free(c->s1);
	if (((c->ready >> 8) & 1) == 1)
		free(c->s2);
	free(c);
}

void	free_info(t_data *info)
{
	int i;

	free(info->textdata);
	free(info->spritedata);
	i = 0;
	while (i < info->num_spr)
	{
		free(info->spt[i]->pos);
		free(info->spt[i]);
		i++;
	}
	free(info->spt);
	free(info->animation);
	free(info->player->pos);
	free(info->player);
	free(info);
}

int		free_exit(t_data *info)
{
	free_cub_file(info->cub_file);
	free_info(info);
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	*info;
	int		fd;

	if (argc == 2 || (argc == 3 && ft_strlen(argv[2]) == 6
				&& ft_strncmp("--save", argv[2], 6) == 0))
	{
		info = init_info(argv);
		info->dark = 0;
		init_wall_tex(info);
		init_sp_tex(info);
		build_image(info, 0);
		if (argc == 3)
		{
			fd = open("./save.bmp", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
			file_type_data(info, fd);
			img_info_data(info, fd);
			raw_pixel_data(info, fd);
			close(fd);
			free_exit(info);
		}
		game_loop(info);
	}
	else
		write(1, "wrong arguments\n", 16);
}
