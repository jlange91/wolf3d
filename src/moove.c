/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:44:28 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 03:47:33 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	forward(t_wolf *wolf)
{
	double pos_x;
	double pos_y;

	pos_x = resize_double(wolf->posx + d_cos(wolf->radius +
				(wolf->fov / 2)) * SPEED_MOOVE);
	pos_y = resize_double(wolf->posy + d_sin(wolf->radius +
				(wolf->fov / 2)) * SPEED_MOOVE);
	if (pos_x >= wolf->map_width || pos_x < 0 ||
			pos_y >= wolf->map_height || pos_y < 0)
		return ;
	if (!wolf->map[(unsigned int)(wolf->posy)][(unsigned int)(pos_x)].type)
		wolf->posx = pos_x;
	if (!wolf->map[(unsigned int)(pos_y)][(unsigned int)(wolf->posx)].type)
		wolf->posy = pos_y;
}

void	backward(t_wolf *wolf)
{
	double pos_x;
	double pos_y;

	pos_x = resize_double(wolf->posx - d_cos(wolf->radius +
				(wolf->fov / 2)) * SPEED_MOOVE);
	pos_y = resize_double(wolf->posy - d_sin(wolf->radius +
				(wolf->fov / 2)) * SPEED_MOOVE);
	if (pos_x >= wolf->map_width || pos_x < 0 ||
			pos_y >= wolf->map_height || pos_y < 0)
		return ;
	if (!wolf->map[(unsigned int)(wolf->posy)][(unsigned int)(pos_x)].type)
		wolf->posx = pos_x;
	if (!wolf->map[(unsigned int)(pos_y)][(unsigned int)(wolf->posx)].type)
		wolf->posy = pos_y;
}
