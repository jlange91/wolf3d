/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:09:00 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 17:06:02 by jlange           ###   ########.fr       */
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
		ft_line(point_a, point_b, &wolf->minimap, BLEU_F);
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

static inline void		draw_map_loop(t_wolf *wolf, t_m *m)
{
	m->x = 0;
	m->rx = resize_double(wolf->posx - (m->max_x / 2));
	m->dx = fmod((wolf->minimap.width / 2) - (wolf->posx
				* wolf->mm_info.square), wolf->mm_info.square);
	m->dx = (m->dx > 0) ? m->dx - wolf->mm_info.square : m->dx;
	while (m->x < m->max_x + 1)
	{
		if (m->ry < wolf->map_height && m->ry >= 0
		&& m->rx < wolf->map_width && m->rx >= 0
		&& wolf->map[(unsigned int)m->ry][(unsigned int)m->rx].type
		&& wolf->map[(unsigned int)m->ry][(unsigned int)m->rx].discover == 1)
		{
			m->point_a.x = (m->x * wolf->mm_info.square) + round(m->dx);
			m->point_a.y = (m->y * wolf->mm_info.square) + round(m->dy);
			m->point_b.x = ((m->x + 1) * wolf->mm_info.square) + round(m->dx);
			m->point_b.y = ((m->y + 1) * wolf->mm_info.square) + round(m->dy);
			ft_draw_rectangle(m->point_a, m->point_b, &wolf->minimap, BLANC);
		}
		m->rx = resize_double(++m->rx);
		++m->x;
	}
	++m->y;
	m->ry = resize_double(++m->ry);
}

void					minimap_draw_map(t_wolf *wolf)
{
	t_m m;

	m.max_x = wolf->minimap.width / wolf->mm_info.square;
	m.max_y = wolf->minimap.height / wolf->mm_info.square;
	m.y = 0;
	m.ry = resize_double(wolf->posy - (m.max_y / 2));
	m.dy = fmod((wolf->minimap.height / 2)
			- (wolf->posy * wolf->mm_info.square), wolf->mm_info.square);
	m.dy = (m.dy > 0) ? m.dy - wolf->mm_info.square : m.dy;
	while (m.y < m.max_y + 1)
		draw_map_loop(wolf, &m);
}
