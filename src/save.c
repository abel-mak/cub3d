/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:00:48 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/10 14:46:28 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

/*
** write_to_buff will write to file in reverse order meaning
** that we start writing from lower significante bit to msb
*/

void	write_to_buff(char *buff, int *start, unsigned int input, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		buff[*start] = (input >> i * 8) & 0xFF;
		(*start)++;
		i++;
	}
}

void	file_type_data(t_data *info, int fd)
{
	char			ftd[14];
	unsigned int	file_size;
	int				start;

	start = 0;
	write_to_buff(ftd, &start, 0x42, 1);
	write_to_buff(ftd, &start, 0x4D, 1);
	file_size = 14 + 40 +
		info->cub_file->w_width * info->cub_file->w_height * 4;
	write_to_buff(ftd, &start, file_size, 4);
	write_to_buff(ftd, &start, 0, 2);
	write_to_buff(ftd, &start, 0, 2);
	write_to_buff(ftd, &start, 54, 4);
	write(fd, ftd, start);
}

void	img_info_data(t_data *info, int fd)
{
	char	iid[40];
	int		start;

	start = 0;
	write_to_buff(iid, &start, 40, 4);
	write_to_buff(iid, &start, info->cub_file->w_width, 4);
	write_to_buff(iid, &start, info->cub_file->w_height, 4);
	write_to_buff(iid, &start, 1, 2);
	write_to_buff(iid, &start, 32, 2);
	write_to_buff(iid, &start, 0, 4);
	write_to_buff(iid, &start, 0, 4);
	write_to_buff(iid, &start, 0, 4);
	write_to_buff(iid, &start, 0, 4);
	write_to_buff(iid, &start, 0, 4);
	write_to_buff(iid, &start, 0, 4);
	write(fd, iid, start);
}

void	raw_pixel_data(t_data *info, int fd)
{
	char	*rpl;
	int		start;
	int		i;
	int		j;

	rpl = (char*)malloc(sizeof(char) *
			(info->cub_file->w_width * info->cub_file->w_height * 4));
	start = 0;
	i = info->cub_file->w_height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < info->cub_file->w_width)
		{
			write_to_buff(rpl, &start, info->data
					[i * info->cub_file->w_width + j], 4);
			j++;
		}
		i--;
	}
	write(fd, rpl, start);
	free(rpl);
}
