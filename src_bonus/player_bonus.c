/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:48:43 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 09:50:35 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	check_next_pos_up(t_data *info, float xcord, float ycord)
{
	t_player	*player;
	char		**map;

	player = info->player;
	map = info->map;
	if (map[(int)((player->pos->y) / BO)]
			[(int)((player->pos->x + xcord) / BO)] != '1'
			&& map[(int)((player->pos->y + ycord) / BO)]
			[(int)((player->pos->x) / BO)] != '1'
			&& map[(int)((player->pos->y + ycord + ycord / 10) / BO)]
			[(int)((player->pos->x + xcord + xcord / 10) / BO)] != '1'
			&& map[(int)((player->pos->y + ycord) / BO)]
			[(int)((player->pos->x + xcord) / BO)] != '2'
			&& map[(int)((player->pos->y + ycord) / BO)]
			[(int)((player->pos->x + xcord) / BO)] != '3')
	{
		info->player->pos->x += xcord;
		info->player->pos->y += ycord;
	}
}

void	set_player_rotangle(t_data *info, int i, int j)
{
	if (info->map[i][j] == 'N')
		info->player->rotangle = 3 * PI / 2;
	else if (info->map[i][j] == 'S')
		info->player->rotangle = PI / 2;
	else if (info->map[i][j] == 'E')
		info->player->rotangle = 0;
	else if (info->map[i][j] == 'W')
		info->player->rotangle = PI;
}

/*
** is_by_player will check if position i, j is situated between
** square were player is in, that square is the size of 20*20
*/

int		is_by_player(t_data *info, int i, int j)
{
	if (abs((int)(info->player->pos->x / BO) - j) < 10
			&& abs((int)(info->player->pos->y / BO) - i) < 10)
		return (1);
	return (0);
}

int		is_pos(char c)
{
	char *pos;

	pos = "NSWE";
	while (*pos != '\0')
	{
		if (*pos == c)
			return (1);
		pos++;
	}
	return (0);
}
