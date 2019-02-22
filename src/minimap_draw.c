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
		// if (wolf->mm_info.px > wolf->minimap.width)
			// point_b.x += wolf->mm_info.restx;
		// if (wolf->mm_info.py > wolf->minimap.height)
			// point_b.y += wolf->mm_info.resty;
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
	double			mx;
	double			my;
	double			x;
	double			y;
	y = 0;
	ry = resize_double(wolf->posY - (max_y / 2));
	my = fmod((wolf->minimap.height / 2) - (wolf->posY * wolf->mm_info.square), wolf->mm_info.square);
	my = (my > 0) ? my - wolf->mm_info.square : my;
	while (y < max_y + 1)
	{
		x = 0;
		rx = resize_double(wolf->posX - (max_x / 2));
		mx = fmod((wolf->minimap.width / 2) - (wolf->posX * wolf->mm_info.square), wolf->mm_info.square);
		mx = (mx > 0) ? mx - wolf->mm_info.square : mx;
		while (x < max_x + 1)
		{
			if (ry < wolf->mapHeigth && ry >= 0 &&
			 		rx < wolf->mapWidth && rx >= 0 &&
					wolf->map[(unsigned int)ry][(unsigned int)rx].type &&
					wolf->map[(unsigned int)ry][(unsigned int)rx].discover == 1)
			{
				point_a.x = (x * wolf->mm_info.square) + round(mx);
				point_a.y = (y * wolf->mm_info.square) + round(my);
				point_b.x = ((x + 1) * wolf->mm_info.square) + round(mx);
				point_b.y = ((y + 1) * wolf->mm_info.square) + round(my);
				ft_draw_rectangle(point_a, point_b, &wolf->minimap, BLANC);
			}
			rx = resize_double(++rx);
			++x;
		}
		++y;
		ry = resize_double(++ry);
	}
}


// void					minimap_draw_map(t_wolf *wolf)
// {
// 	double max_x = wolf->minimap.width / wolf->mm_info.square;
// 	double max_y = wolf->minimap.height / wolf->mm_info.square;
// 	t_point		point_a;
// 	t_point		point_b;
// 	double			rx;
// 	double			ry;
// 	double			mx;
// 	double			my;
// 	double			x;
// 	double			y;
// 	y = 0;
// 	ry = (wolf->posY - (max_y / 2));
// 	my = fmod((wolf->minimap.height / 2) - (wolf->posY * wolf->mm_info.square), wolf->mm_info.square);
// 	my = (my > 0) ? my - wolf->mm_info.square : my;
// 	while (y < max_y + 1)
// 	{
// 		x = 0;
// 		rx = (wolf->posX - (max_x / 2));
// 		mx = fmod((wolf->minimap.width / 2) - (wolf->posX * wolf->mm_info.square), wolf->mm_info.square);
// 		mx = (mx > 0) ? mx - wolf->mm_info.square : mx;
// 		while (x < max_x + 1)
// 		{
// 			if (ry < wolf->mapHeigth && ry >= 0 &&
// 					rx < wolf->mapWidth && rx >= 0 &&
// 					wolf->map[(int)ry][(int)rx])
// 			{
// 				point_a.x = (x * wolf->mm_info.square) + round(mx);
// 				point_a.y = (y * wolf->mm_info.square) + round(my);
// 				point_b.x = ((x + 1) * wolf->mm_info.square) + round(mx);
// 				point_b.y = ((y + 1) * wolf->mm_info.square) + round(my);
// 				ft_draw_rectangle(point_a, point_b, &wolf->minimap, BLANC);
// 			}
// 			++rx;
// 			++x;
// 		}
// 		++y;
// 		++ry;
// 	}
// }

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
