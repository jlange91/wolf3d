/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:11:17 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 03:11:45 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_dpoint	find_dist(double angle)
{
	double		x_a;
	double		y_a;
	t_dpoint	dist;

	x_a = fabs(1 / d_tan(angle));
	y_a = fabs(1 * d_tan(angle));
	dist.x = sqrt(x_a * x_a + 1);
	dist.y = sqrt(y_a * y_a + 1);
	return (dist);
}

t_dpoint	find_first_dist(double pos_x, double pos_y, double angle)
{
	double		x;
	double		y;
	double		x_a;
	double		y_a;
	t_dpoint	dist;

	x = (angle > 90 && angle < 270) ? fabs(fmod(pos_x, 1)) :
		fabs(fmod(pos_x, 1) - 1);
	y = (angle > 180) ? fabs(fmod(pos_y, 1)) :
		fabs(fmod(pos_y, 1) - 1);
	x_a = fabs(y / d_tan(angle));
	y_a = fabs(x * d_tan(angle));
	dist.x = sqrt(x_a * x_a + y * y);
	dist.y = sqrt(y_a * y_a + x * x);
	return (dist);
}

t_si		init_search_intersection(t_wolf *wolf, t_intersection inter)
{
	t_si i;

	i.dist = find_dist(inter.angle);
	i.first_dist = find_first_dist(wolf->posx, wolf->posy, inter.angle);
	if (inter.angle > 90 && inter.angle < 270)
		i.stepx = -1;
	else
		i.stepx = 1;
	if (inter.angle > 180)
		i.stepy = -1;
	else
		i.stepy = 1;
	i.mapx = (int)wolf->posx;
	i.mapy = (int)wolf->posy;
	i.hit = 0;
	return (i);
}
