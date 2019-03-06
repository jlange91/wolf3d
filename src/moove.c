/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 03:44:28 by jlange            #+#    #+#             */
/*   Updated: 2019/03/05 02:52:49 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	forward(t_wolf *wolf)
{
	double pos_x;
	double pos_y;

	pos_x = wolf->posx + d_cos(wolf->radius
				+ (wolf->fov / 2)) * (SPEED_MOOVE + (wolf->key[SHIFT] * 0.3));
	pos_y = wolf->posy + d_sin(wolf->radius
				+ (wolf->fov / 2)) * (SPEED_MOOVE + (wolf->key[SHIFT] * 0.3));
	if (pos_x >= wolf->map_width || pos_x < 0
			|| pos_y >= wolf->map_height || pos_y < 0)
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

	pos_x = wolf->posx - d_cos(wolf->radius
				+ (wolf->fov / 2)) * (SPEED_MOOVE + (wolf->key[SHIFT] * 0.3));
	pos_y = wolf->posy - d_sin(wolf->radius
				+ (wolf->fov / 2)) * (SPEED_MOOVE + (wolf->key[SHIFT] * 0.3));
	if (pos_x >= wolf->map_width || pos_x < 0
			|| pos_y >= wolf->map_height || pos_y < 0)
		return ;
	if (!wolf->map[(unsigned int)(wolf->posy)][(unsigned int)(pos_x)].type)
		wolf->posx = pos_x;
	if (!wolf->map[(unsigned int)(pos_y)][(unsigned int)(wolf->posx)].type)
		wolf->posy = pos_y;
}
