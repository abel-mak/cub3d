/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:23:55 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/10 14:45:11 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	swap(float *a, float *b)
{
	float c;

	c = *a;
	*a = *b;
	*b = c;
}

/*
** trans_x => translate box_x
** trans_y => translate box_y
*/

t_point	*pnt(float x, float y)
{
	t_point *res;

	res = malloc(sizeof(t_point));
	res->x = x;
	res->y = y;
	return (res);
}

float	dist(t_point *a, t_point *b)
{
	float res;

	res = sqrtf(powf(b->x - a->x, 2) + powf(b->y - a->y, 2));
	return (res);
}
