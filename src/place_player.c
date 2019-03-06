/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:47:04 by jlange            #+#    #+#             */
/*   Updated: 2019/03/06 07:29:41 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline int	in_middle2(t_wolf *wolf)
{
	if (!wolf->map[(int)(wolf->map_height / 2.0 - 1)][(int)(wolf->map_width
				/ 2.0)].type)
	{
		wolf->posy = wolf->map_height / 2.0 - 1;
		wolf->posx = wolf->map_width / 2.0;
	}
	else if (!wolf->map[(int)(wolf->map_height / 2.0)][(int)(wolf->map_width
				/ 2.0 - 1)].type)
	{
		wolf->posy = wolf->map_height / 2.0;
		wolf->posx = wolf->map_width / 2.0 - 1;
	}
	else
		return (1);
	return (0);
}

static inline int	in_middle1(t_wolf *wolf)
{
	if (!wolf->map[(int)(wolf->map_height / 2.0)][(int)(wolf->map_width
				/ 2.0 + 1)].type)
	{
		wolf->posy = wolf->map_height / 2.0;
		wolf->posx = wolf->map_width / 2.0 + 1;
	}
	else if (!wolf->map[(int)(wolf->map_height / 2.0 + 1)][(int)(wolf->map_width
				/ 2.0)].type)
	{
		wolf->posy = wolf->map_height / 2.0 + 1;
		wolf->posx = wolf->map_width / 2.0;
	}
	else
		return (in_middle2(wolf));
	return (0);
}

int					place_player(t_wolf *wolf)
{
	int		y;
	int		x;

	y = 0;
	if (wolf->map_height % 2 && wolf->map_width % 2
		&& wolf->map_height > 1 && wolf->map_width > 1 && in_middle1(wolf) == 0)
		return (0);
	while (y < wolf->map_height)
	{
		x = 0;
		while (x < wolf->map_width)
		{
			if (wolf->map[y][x].type == 0)
			{
				wolf->posx = x + 0.5;
				wolf->posy = y + 0.5;
				return (0);
			}
			++x;
		}
		++y;
	}
	return (5);
}
