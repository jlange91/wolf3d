/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 00:42:31 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 03:35:25 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void	check_map(t_wolf *wolf, t_si *i)
{
	if ((i->mapx >= 0 && i->mapx < wolf->map_width)
			&& (i->mapy >= 0 && i->mapy < wolf->map_height)
			&& (wolf->map[i->mapy][i->mapx].type > 0
			|| wolf->map[i->mapy][i->mapx].win == 1))
	{
		i->hit = 1;
		wolf->map[i->mapy][i->mapx].discover = 1;
	}
}

static inline void	raycasting(t_wolf *wolf, t_intersection *inter, t_si *i)
{
	while (i->hit == 0)
	{
		if (i->first_dist.x < i->first_dist.y || i->first_dist.y == INFINITY)
		{
			if (i->first_dist.x >= wolf->length_view)
				break ;
			inter->dist = i->first_dist.x;
			inter->hit = (inter->angle > 180) ? 1 : 2;
			i->first_dist.x += i->dist.x;
			i->mapy = i->mapy + i->stepy;
		}
		else
		{
			if (i->first_dist.y >= wolf->length_view)
				break ;
			inter->dist = i->first_dist.y;
			inter->hit = (inter->angle > 90 && inter->angle < 270) ? 3 : 4;
			i->first_dist.y += i->dist.y;
			i->mapx = i->mapx + i->stepx;
		}
		check_map(wolf, i);
	}
}

static inline void	remove_fisheyes(t_wolf *wolf, t_intersection *inter)
{
	double middle;
	double angle;
	double diff;

	if (!wolf->fisheyes)
	{
		middle = wolf->radius + (wolf->fov / 2);
		angle = (inter->angle < wolf->radius)
			? inter->angle + 360 : inter->angle;
		diff = (middle > angle) ? angle - middle : middle - angle;
		inter->dist_wfe = inter->dist * d_cos(diff);
	}
	else
		inter->dist_wfe = inter->dist;
}

t_intersection		search_intersection(t_wolf *wolf, t_intersection inter)
{
	t_si i;

	i = init_search_intersection(wolf, inter);
	raycasting(wolf, &inter, &i);
	inter.win = ((i.mapx >= 0 && i.mapx < wolf->map_width)
			&& (i.mapy >= 0 && i.mapy < wolf->map_height)
			&& wolf->map[i.mapy][i.mapx].win == 1) ? 1 : 0;
	if (i.hit == 0)
	{
		inter.dist = wolf->length_view;
		inter.hit = 0;
	}
	if (inter.hit == 0)
		inter.color = 0;
	else if (inter.hit == 1)
		inter.color = BLEU_C;
	else if (inter.hit == 2)
		inter.color = VERT_C;
	else if (inter.hit == 3)
		inter.color = JAUNE;
	else if (inter.hit == 4)
		inter.color = BLANC;
	inter.point = endpoint2(inter.angle, wolf->posx, wolf->posy, inter.dist);
	remove_fisheyes(wolf, &inter);
	return (inter);
}

void				search_intersections(t_wolf *wolf)
{
	t_point		map0;
	double		start_angle;
	int			i;

	i = 0;
	map0.x = wolf->posx;
	map0.y = wolf->posy;
	start_angle = wolf->radius;
	wolf->space_inter_radius = (double)wolf->fov / (double)WIN_X;
	while (i < WIN_X)
	{
		wolf->inter[i].angle = start_angle;
		wolf->inter[i] = search_intersection(wolf, wolf->inter[i]);
		wolf->inter[i].wall = WIN_Y / wolf->inter[i].dist_wfe;
		start_angle += wolf->space_inter_radius;
		start_angle -= (start_angle >= 360.) ? 360 : 0;
		++i;
	}
}
