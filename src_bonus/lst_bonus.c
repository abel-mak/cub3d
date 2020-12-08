/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:45:56 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/11 09:52:07 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

t_li	*lst_new(void *content)
{
	t_li *new;

	new = (t_li*)malloc(sizeof(t_li));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	lst_add_back(t_li *head, void *content)
{
	t_li *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
		{
			tmp->next = lst_new(content);
			return ;
		}
		tmp = tmp->next;
	}
}

void	lst_free(t_li *head)
{
	if (head == NULL)
		return ;
	if (head->next != NULL)
		lst_free(head->next);
	free(head->content);
	free(head);
}

int		lst_len(t_li *head)
{
	int len;

	len = 0;
	while (head != NULL)
	{
		len++;
		head = head->next;
	}
	return (len);
}

void	lst_add_front(t_li **head, void *content)
{
	t_li *new;

	new = lst_new(content);
	new->next = (*head);
	(*head) = new;
}
