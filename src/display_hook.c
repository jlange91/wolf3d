/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 22:32:51 by jlange            #+#    #+#             */
/*   Updated: 2018/04/10 18:50:09 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// static inline void		ft_display_hook1(int keycode, t_mlx *mlx)
// {
// 	if (keycode == MINUS || keycode == PLUS)
// 	{
// 		if (keycode == PLUS)
// 		{
// 		}
// 		else
// 			;
// 		ft_display_img((t_mlx*)mlx);
// 	}
// 	else
// 		ft_display_hook2(keycode, mlx);
// }

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

			posX = wolf->posX + dCos(wolf->radius + (FOV / 2)) * SPEED_MOOVE;
			posY = wolf->posY + dSin(wolf->radius + (FOV / 2)) * SPEED_MOOVE;
			if (posX >= wolf->mapWidth || posX < 0 ||
				 posY >= wolf->mapHeigth || posY < 0)
				return (0);
			if (!wolf->map[(int)(wolf->posY)][(int)(posX)])
				wolf->posX = posX;
			if (!wolf->map[(int)(posY)][(int)(wolf->posX)])
				wolf->posY = posY;
		}
		else
		{
			double posX;
			double posY;

			posX = wolf->posX - dCos(wolf->radius + (FOV / 2)) * SPEED_MOOVE;
			posY = wolf->posY - dSin(wolf->radius + (FOV / 2)) * SPEED_MOOVE;
			if (posX >= wolf->mapWidth || posX < 0 ||
				 posY >= wolf->mapHeigth || posY < 0)
				return (0);
			if (!wolf->map[(int)(wolf->posY)][(int)(posX)])
				wolf->posX = posX;
			if (!wolf->map[(int)(posY)][(int)(wolf->posX)])
				wolf->posY = posY;
		}
		ft_wolf(wolf);
	}
	else if (keycode == FISHEYES)
	{
		wolf->fisheyes = (wolf->fisheyes == 0) ? 1 : 0;
		ft_wolf(wolf);
	}
	// else
	// 	ft_display_hook1(keycode, test);
	return (0);
}
