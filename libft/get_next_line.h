/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:14:51 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/09 12:13:34 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 32
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_list	t_list;
struct					s_list
{
	int		fd;
	char	*savedstr;
	t_list	*next;
};
int						fill_line(char **buff, char **line,
	t_list **lst, t_list **head);
int						get_next_line(int fd, char **line);
t_list					*ladd(t_list **head, t_list *new);
t_list					*lnew(char *savedstr, int fd);
int						ft_lstclear(char **line, t_list **lst, t_list **head,
	int reset);
t_list					*loop_l(t_list *head, int fd);

#endif
