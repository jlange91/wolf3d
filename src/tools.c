/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:51:53 by jlange            #+#    #+#             */
/*   Updated: 2018/04/10 16:46:08 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_dpoint endpoint2(double angle, double x1 , double y1, double lenght)
{
		t_dpoint ret;
    double radians = (M_PI/180) * angle;

    double x2 = x1 + (lenght * cos(radians));
    double y2 = y1 + (lenght * sin(radians));
		ret.x = x2;
		ret.y = y2;
		// printf("endpoint %f %f\n", x2, y2);

    return (ret);
}

t_point endpoint(double angle, int x1 , int y1, double lenght)
{
		t_point ret;
    double radians = (M_PI/180)*angle;

    double x2 = x1 + (lenght * cos(radians));
    double y2 = y1 + (lenght * sin(radians));
		ret.x = round(x2);
		ret.y = round(y2);

    return (ret);
}

void	ft_pixel_put(t_image *img, int x, int y, int color)
{
	int pixel;

	pixel = (y * img->width) + x;
	if (x > 0 && x < img->width - 1 && y > 0 && y < img->height - 1 && pixel > img->width)
		img->img[pixel] = color;
}

void	ft_line_wall(t_point map0, t_point map1, t_image *img, int color)
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
	while (1)
	{
		if ((map0.x == map1.x && map0.y == map1.y))
			break ;
		ft_pixel_put(img, map0.x, map0.y, color);
		l.e2 = l.err;
		l.err -= (l.e2 > -l.dx) ? l.dy : 0;
		map0.x += (l.e2 > -l.dx) ? l.sx : 0;
		l.err += (l.e2 < l.dy) ? l.dx : 0;
		map0.y += (l.e2 < l.dy) ? l.sy : 0;
	}
}

void	ft_line(t_point map0, t_point map1, t_image *img, int color)
{
	t_line l;

	l.dy = abs(map1.y - map0.y);
	l.dx = abs(map1.x - map0.x);
	l.sx = map0.x < map1.x ? 1 : -1;
	l.sy = map0.y < map1.y ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		if ((map0.x == map1.x && map0.y == map1.y))
			break ;
		ft_pixel_put(img, map0.x, map0.y, color);
		l.e2 = l.err;
		l.err -= (l.e2 > -l.dx) ? l.dy : 0;
		map0.x += (l.e2 > -l.dx) ? l.sx : 0;
		l.err += (l.e2 < l.dy) ? l.dx : 0;
		map0.y += (l.e2 < l.dy) ? l.sy : 0;
	}
}

void      ft_draw_rectangle(t_point map0, t_point map1, t_image *img, int color)
{
	t_point pointA;
	t_point pointB;

	while (map0.x < map1.x)
	{
		pointA.x = map0.x;
		pointA.y = map0.y;
		pointB.x = map0.x;
		pointB.y = map1.y;
		ft_line(pointA, pointB, img, color);
		map0.x += 1;
	}
}

int		ft_redcross(t_wolf *wolf)
{
	ft_free(wolf);
	exit(0);
}

double toRadian(double degree)
{
	return ((degree) * M_PI / 180.0);
}

double	dCos(double degree)
{
	return cos(toRadian(degree));
}

double	dSin(double degree)
{
	return sin(toRadian(degree));
}

double	dTan(double degree)
{
	return tan(toRadian(degree));
}
