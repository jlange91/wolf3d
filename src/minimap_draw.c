/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:09:00 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:38:08 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void					minimap_draw_angle(t_wolf *wolf)
{
	int			i;
	t_point		point_a;
	t_point		point_b;

	i = -1;
	point_a.x = WIN_X_MINIMAP / 2;
	point_a.y = WIN_Y_MINIMAP / 2;
	if (wolf->mm_info.px > wolf->minimap.width)
		point_a.x += wolf->mm_info.restx;
	if (wolf->mm_info.py > wolf->minimap.height)
		point_a.y += wolf->mm_info.resty;
	while (++i < WIN_X)
	{
		point_b = endpoint(wolf->inter[i].angle,
				WIN_X_MINIMAP / 2,
				WIN_Y_MINIMAP / 2,
				wolf->inter[i].dist * wolf->mm_info.square);
		if (wolf->mm_info.px > wolf->minimap.width)
			point_b.x += wolf->mm_info.restx;
		if (wolf->mm_info.py > wolf->minimap.height)
			point_b.y += wolf->mm_info.resty;
		ft_line(point_a, point_b, &wolf->minimap, BLEU_F);
	}
}

void					minimap_draw_map(t_wolf *wolf)
{
	double max_x = wolf->minimap.width / wolf->mm_info.square;
	double max_y = wolf->minimap.height / wolf->mm_info.square;
	t_point		point_a;
	t_point		point_b;
	double			rx;
	double			ry;
	int			mx;
	int			my;
	double			x;
	double			y;

	y = 0;
	ry = wolf->posY - (max_y / 2);
	my = fabs(fmod(wolf->posY, 1) - 1) * wolf->mm_info.square;
	while (y < max_y)
	{
		x = 0;
		rx = wolf->posX - (max_x / 2);
		mx = fabs(fmod(wolf->posX, 1) - 1) * wolf->mm_info.square;
		while (x < max_x)
		{
			if (ry < wolf->mapHeigth && ry >= 0 &&
					rx < wolf->mapWidth && rx >= 0 &&
					wolf->map[(int)ry][(int)rx])
			{
				point_a.x = (mx - wolf->mm_info.square);
				point_a.y = (my - wolf->mm_info.square);
				point_b.x = mx;
				point_b.y = my;
				ft_draw_rectangle(point_a, point_b, &wolf->minimap, BLANC);
			}
			++rx;
			++x;
			mx += wolf->mm_info.square;
		}
		++y;
		++ry;
		my += wolf->mm_info.square;
	}
}

void					minimap_draw_cadriage(t_wolf *wolf)
{
	t_point		point_a;
	t_point		point_b;
	int			y;
	int			x;

	y = 0;
	x = 0;
	while (y < wolf->minimap.height / wolf->mm_info.square)
	{
		point_a.x = 0 + (fmod(wolf->posX, 1) * wolf->mm_info.square);
		point_a.y = y * wolf->mm_info.square - 1 + (fmod(wolf->posY, 1) * wolf->mm_info.square);
		point_b.x = wolf->minimap.width - 1 + (fmod(wolf->posX, 1) * wolf->mm_info.square);
		point_b.y = y * wolf->mm_info.square - 1 + (fmod(wolf->posY, 1) * wolf->mm_info.square);
		ft_line(point_a, point_b, &wolf->minimap, BLANC);
		++y;
	}
	while (x < wolf->minimap.width / wolf->mm_info.square)
	{
		point_a.x = x * wolf->mm_info.square - 1 + (fmod(wolf->posX, 1) * wolf->mm_info.square);
		point_a.y = 0 + (fmod(wolf->posY, 1) * wolf->mm_info.square);
		point_b.x = x * wolf->mm_info.square - 1 + (fmod(wolf->posX, 1) * wolf->mm_info.square);
		point_b.y = wolf->minimap.height - 1 + (fmod(wolf->posY, 1) * wolf->mm_info.square);
		ft_line(point_a, point_b, &wolf->minimap, BLANC);
		++x;
	}
}

void					minimap_draw_perso(t_wolf *wolf)
{
	t_point point_a;
	t_point point_b;

	point_a.x = WIN_X_MINIMAP / 2 - 1;
	point_a.y = WIN_Y_MINIMAP / 2 - 1;
	point_b.x = WIN_X_MINIMAP / 2 + 1;
	point_b.y = WIN_Y_MINIMAP / 2 + 1;
	if (wolf->mm_info.px > wolf->minimap.width)
	{
		point_a.x += wolf->mm_info.restx;
		point_b.x += wolf->mm_info.restx;
	}
	if (wolf->mm_info.py > wolf->minimap.height)
	{
		point_a.y += wolf->mm_info.resty;
		point_b.y += wolf->mm_info.resty;
	}
	ft_draw_rectangle(point_a, point_b, &wolf->minimap, 0x00FF0000);
}
