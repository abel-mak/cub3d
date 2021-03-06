/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:15:42 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/15 11:24:13 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int		israydown(float angle)
{
	if (angle > 0 && angle < PI)
		return (1);
	return (0);
}

int		israyright(float angle)
{
	if (angle < PI / 2 || angle > 3 * PI / 2)
		return (1);
	return (0);
}

/*
** normalize from [-PI, PI]
*/

float	minuspitopi(float angle)
{
	angle = fmodf(angle + PI, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle - PI);
}

float	normalize(float angle)
{
	float res;

	res = fmodf(angle, (2 * PI));
	if (res < 0)
		res += 2 * PI;
	return (res);
}
