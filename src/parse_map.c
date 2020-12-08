/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:39:25 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/10 13:43:32 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int		start_map(char *line)
{
	if (*line == 0)
		return (0);
	while (*line != '\0')
	{
		if (*line != ' ' && *line != '1' && is_inner(*line) == 0)
			return (0);
		line++;
	}
	return (1);
}

void	add_space(t_li *head, size_t max_len)
{
	char *tmp;
	char *tmp2;
	char *space_line;

	while (head != NULL)
	{
		tmp = head->content;
		tmp2 = ft_strjoin(" ", tmp);
		space_line = (char*)malloc(((max_len + 1) - ft_strlen(tmp2) + 1) + 1);
		ft_memset(space_line, ' ', (max_len - ft_strlen(tmp2) + 2));
		space_line[(max_len - ft_strlen(tmp2) + 2)] = '\0';
		head->content = ft_strjoin(tmp2, space_line);
		free(tmp);
		free(tmp2);
		free(space_line);
		head = head->next;
	}
}

size_t	add_space_top_bottom(t_li **head)
{
	size_t	max_len;
	char	*space_line;
	t_li	*tmp;

	max_len = 0;
	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strlen((char*)tmp->content) > max_len)
			max_len = ft_strlen((char*)tmp->content);
		tmp = tmp->next;
	}
	space_line = (char*)malloc(sizeof(char) * (max_len + 1));
	ft_memset(space_line, ' ', max_len);
	space_line[max_len] = '\0';
	lst_add_back(*head, ft_strdup(space_line));
	lst_add_front(head, ft_strdup(space_line));
	free(space_line);
	return (max_len);
}

char	**map_to_array(t_li *head)
{
	size_t	map_h;
	char	**res;
	size_t	i;

	map_h = lst_len(head);
	res = (char**)malloc(sizeof(char*) * (map_h));
	i = 0;
	while (head != NULL)
	{
		res[i] = ft_strdup((char*)head->content);
		i++;
		head = head->next;
	}
	return (res);
}

/*
** the idea of get_map is first to get map from .cub file
** and then get it circled with space from left and right
** top and bottom and will make it easy to find errors
** add 2 max_len for added space in front and back of line
*/

int		get_map(t_file *cub_file, char *line)
{
	int			r;
	t_li		*head;

	head = lst_new(ft_strdup(line));
	r = 1;
	while (r == 1)
	{
		r = get_next_line(cub_file->fd, &line);
		if (*line != '\0')
		{
			if (start_map(line) == 0)
			{
				free(line);
				map_error(700, 700);
			}
			lst_add_back(head, ft_strdup(line));
		}
		else if (*line == '\0')
			r = 0;
		free(line);
	}
	set_value(cub_file, &head);
	check_c(cub_file->map, cub_file);
	lst_free(head);
	return (1);
}
