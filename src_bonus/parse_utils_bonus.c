/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:54:15 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 10:00:51 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int		check_path(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int		get_path(char **path, char *line)
{
	char *tmp;

	tmp = ft_strtrim(line, " ");
	*path = ft_strdup(tmp);
	free(tmp);
	if (check_path(*path) == 0)
		put_error("error parsing path");
	return (1);
}

void	set_value(t_file *cub_file, t_li **head)
{
	size_t		max_len;

	max_len = add_space_top_bottom(head);
	add_space(*head, max_len);
	cub_file->map = map_to_array(*head);
	cub_file->map_h = (int)lst_len(*head);
	cub_file->map_w = (int)ft_strlen(cub_file->map[0]);
}
