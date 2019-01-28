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
	point_a.x = fmod(wolf->posX * MINIMAP_ZOOM, wolf->minimap.width);
	point_a.y = fmod(wolf->posY * MINIMAP_ZOOM, wolf->minimap.height);
	if (wolf->mm_info.px > wolf->minimap.width)
		point_a.x += wolf->mm_info.restx;
	if (wolf->mm_info.py > wolf->minimap.height)
		point_a.y += wolf->mm_info.resty;
	while (++i < WIN_X)
	{
		point_b = endpoint(wolf->inter[i].angle,
				fmod((wolf->posX * MINIMAP_ZOOM), wolf->minimap.width),
				fmod((wolf->posY * MINIMAP_ZOOM), wolf->minimap.height),
				wolf->inter[i].dist * MINIMAP_ZOOM);
		if (wolf->mm_info.px > wolf->minimap.width)
			point_b.x += wolf->mm_info.restx;
		if (wolf->mm_info.py > wolf->minimap.height)
			point_b.y += wolf->mm_info.resty;
		ft_line(point_a, point_b, &wolf->minimap, BLEU_F);
	}
}

void					minimap_draw_map(t_wolf *wolf)
{
	t_point		point_a;
	t_point		point_b;
	int			x;
	int			y;
	int			mult_x = ((wolf->posX * MINIMAP_ZOOM) / wolf->minimap.width);
	int			mult_y = ((wolf->posY * MINIMAP_ZOOM) / wolf->minimap.height);

	y = 0;
	while (y < wolf->minimap.height / wolf->mm_info.square)
	{
		x = 0;
		while (x < wolf->minimap.width / wolf->mm_info.square)
		{
			int rx = x + ((wolf->minimap.width / wolf->mm_info.square) * mult_x);
			int ry = y + ((wolf->minimap.height / wolf->mm_info.square) * mult_y);
			if (ry < wolf->mapHeigth &&
					rx < wolf->mapWidth &&
					wolf->map[ry][rx])
			{
				point_a.x = x * wolf->mm_info.square;
				point_a.y = y * wolf->mm_info.square;
				point_b.x = (x + 1) * wolf->mm_info.square;
				point_b.y = (y + 1) * wolf->mm_info.square;
				ft_draw_rectangle(point_a, point_b, &wolf->minimap, BLANC);
			}
			++x;
		}
		++y;
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
		point_a.x = 0;
		point_a.y = y * wolf->mm_info.square - 1;
		point_b.x = wolf->minimap.width - 1;
		point_b.y = y * wolf->mm_info.square - 1;
		ft_line(point_a, point_b, &wolf->minimap, BLANC);
		++y;
	}
	while (x < wolf->minimap.width / wolf->mm_info.square)
	{
		point_a.x = x * wolf->mm_info.square - 1;
		point_a.y = 0;
		point_b.x = x * wolf->mm_info.square - 1;
		point_b.y = wolf->minimap.height - 1;
		ft_line(point_a, point_b, &wolf->minimap, BLANC);
		++x;
	}
}

void					minimap_draw_perso(t_wolf *wolf)
{
	t_point point_a;
	t_point point_b;

	point_a.x = fmod(wolf->mm_info.px, wolf->minimap.width) - 1;
	point_a.y = fmod(wolf->mm_info.py, wolf->minimap.height) - 1;
	point_b.x = fmod(wolf->mm_info.px, wolf->minimap.width) + 1;
	point_b.y = fmod(wolf->mm_info.py, wolf->minimap.height) + 1;
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
