/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 22:32:51 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:54:42 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		ft_display_hook1(int keycode, t_wolf *wolf)
{
	if (keycode == MINUS || keycode == PLUS)
	{
		if (keycode == PLUS)
			wolf->mm_info.square += 1;
		else
			wolf->mm_info.square -= (wolf->mm_info.square > 1 ) ? 1 : 0;
		ft_wolf(wolf);
	}
}

double resize_double(double nb)
{
	double ret;

	ret = 0;
	if (nb < 0)
		ret = nb + SIZE_INFINY_MAP;
	else if (nb >= SIZE_INFINY_MAP)
		ret = nb - SIZE_INFINY_MAP;
	else
		ret = nb;
	return (ret);
}

int						ft_display_hook(int keycode, void *test)
{
	t_wolf *wolf;


	wolf = (t_wolf*)test;
	if (keycode == ESC)
	{
		ft_free(wolf);
		exit(0);
	}
	else if (keycode == RIGHT || keycode == LEFT)
	{
		if (keycode == RIGHT)
		{
			wolf->radius = wolf->radius + SPEED_ROT;
			wolf->radius -= (wolf->radius >= 360.) ? 360 : 0;
		}
		else
		{
			wolf->radius = wolf->radius - SPEED_ROT;
			wolf->radius += (wolf->radius < 0.) ? 360 : 0;
		}
		ft_wolf(wolf);
	}
	else if (keycode == DOWN || keycode == UP)
	{
		if (keycode == UP)
		{
			double posX;
			double posY;

			posX = resize_double(wolf->posX + d_cos(wolf->radius + (FOV / 2)) * SPEED_MOOVE);
			posY = resize_double(wolf->posY + d_sin(wolf->radius + (FOV / 2)) * SPEED_MOOVE);
			if (posX >= wolf->mapWidth || posX < 0 ||
				 posY >= wolf->mapHeigth || posY < 0)
				return (0);
			if (!wolf->map[(unsigned int)(wolf->posY)][(unsigned int)(posX)].type)
				wolf->posX = posX;
			if (!wolf->map[(unsigned int)(posY)][(unsigned int)(wolf->posX)].type)
				wolf->posY = posY;

		}
		else
		{
			double posX;
			double posY;

			posX = resize_double(wolf->posX - d_cos(wolf->radius + (FOV / 2)) * SPEED_MOOVE);
			posY = resize_double(wolf->posY - d_sin(wolf->radius + (FOV / 2)) * SPEED_MOOVE);
			if (posX >= wolf->mapWidth || posX < 0 ||
				 posY >= wolf->mapHeigth || posY < 0)
				return (0);
			if (!wolf->map[(unsigned int)(wolf->posY)][(unsigned int)(posX)].type)
				wolf->posX = posX;
			if (!wolf->map[(unsigned int)(posY)][(unsigned int)(wolf->posX)].type)
				wolf->posY = posY;
		}
		ft_wolf(wolf);
	}
	else if (keycode == FISHEYES)
	{
		wolf->fisheyes = (wolf->fisheyes == 0) ? 1 : 0;
		ft_wolf(wolf);
	}
	else
		ft_display_hook1(keycode, wolf);
	return (0);
}
