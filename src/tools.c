/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:51:53 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 00:39:35 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

unsigned int	set_color(double dist, unsigned int color, int length_view)
{
	unsigned int coef;
	unsigned int red;
	unsigned int green;
	unsigned int blue;

	coef = dist * 100 / length_view;
	red = ((color & 0xFF0000) >> 16) * (100 - coef) / 100;
	red = (red > 0xFF) ? 0 : red;
	green = ((color & 0xFF00) >> 8) * (100 - coef) / 100;
	green = (green > 0xFF) ? 0 : green;
	blue = ((color & 0xFF)) * (100 - coef) / 100;
	blue = (blue > 0xFF) ? 0 : blue;
	color = (red << 16) + (color & 0x00FFFF);
	color = (green << 8) + (color & 0xFF00FF);
	color = blue + (color & 0xFFFF00);
	return (color);
}

void			ft_pixel_put(t_image *img, int x, int y, int color)
{
	int pixel;

	pixel = (y * img->width) + x;
	if (x > 0 && x < img->width && y > 0
		&& y < img->height && pixel > img->width)
		img->img[pixel] = color;
}

void			ft_line_wall(t_point map0, t_point map1, t_image *img,
		int color)
{
	t_line l;

	map0.x = (map0.x < 0) ? 0 : map0.x;
	map0.x = (map0.x > img->width - 1) ? img->width - 1 : map0.x;
	map1.x = (map1.x < 0) ? 0 : map1.x;
	map1.x = (map1.x > img->width - 1) ? img->width - 1 : map1.x;
	map0.y = (map0.y < 0) ? 0 : map0.y;
	map0.y = (map0.y > img->height - 1) ? img->height - 1 : map0.y;
	map1.y = (map1.y < 0) ? 0 : map1.y;
	map1.y = (map1.y > img->height - 1) ? img->height - 1 : map1.y;
	l.dy = abs(map1.y - map0.y);
	l.dx = abs(map1.x - map0.x);
	l.sx = map0.x < map1.x ? 1 : -1;
	l.sy = map0.y < map1.y ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (!(map0.x == map1.x && map0.y == map1.y))
	{
		ft_pixel_put(img, map0.x, map0.y, color);
		l.e2 = l.err;
		l.err -= (l.e2 > -l.dx) ? l.dy : 0;
		map0.x += (l.e2 > -l.dx) ? l.sx : 0;
		l.err += (l.e2 < l.dy) ? l.dx : 0;
		map0.y += (l.e2 < l.dy) ? l.sy : 0;
	}
}

void			ft_line(t_point map0, t_point map1, t_image *img, int color)
{
	t_line l;

	l.dy = abs(map1.y - map0.y);
	l.dx = abs(map1.x - map0.x);
	l.sx = map0.x < map1.x ? 1 : -1;
	l.sy = map0.y < map1.y ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (!(map0.x == map1.x && map0.y == map1.y))
	{
		ft_pixel_put(img, map0.x, map0.y, color);
		l.e2 = l.err;
		l.err -= (l.e2 > -l.dx) ? l.dy : 0;
		map0.x += (l.e2 > -l.dx) ? l.sx : 0;
		l.err += (l.e2 < l.dy) ? l.dx : 0;
		map0.y += (l.e2 < l.dy) ? l.sy : 0;
	}
}

void			ft_draw_rectangle(t_point map0, t_point map1, t_image *img,
		int color)
{
	t_point point_a;
	t_point point_b;

	while (map0.x < map1.x)
	{
		point_a.x = map0.x;
		point_a.y = map0.y;
		point_b.x = map0.x;
		point_b.y = map1.y;
		ft_line(point_a, point_b, img, color);
		map0.x += 1;
	}
}
