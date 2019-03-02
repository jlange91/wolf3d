/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:04:57 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 00:42:01 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

static int		place_player(t_wolf *wolf)
{
	int		y;
	int		x;

	y = 0;
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

t_map			**create_map(t_wolf *wolf)
{
	t_map	**ret;
	int		i;
	int		j;

	i = 0;
	srand(time(NULL));
	ret = (t_map**)malloc(sizeof(t_map*) * SIZE_INFINY_MAP);
	while (i < SIZE_INFINY_MAP)
	{
		j = -1;
		ret[i] = (t_map*)malloc(sizeof(t_map) * SIZE_INFINY_MAP);
		while (++j < SIZE_INFINY_MAP)
		{
			ret[i][j].type = ((rand() % 100) > BLOCKS_PERCENT) ? 1 : 0;
			ret[i][j].discover = wolf->discover;
		}
		++i;
	}
	wolf->map_width = SIZE_INFINY_MAP;
	wolf->map_height = SIZE_INFINY_MAP;
	return (ret);
}

int				ft_init(t_wolf *wolf, int ac, char **av)
{
	wolf->discover = DISCOVER;
	if (ac > 1)
	{
		if ((wolf->error = ft_fill_tab(wolf, av)))
			return (wolf->error);
	}
	else
		wolf->map = create_map(wolf);
	if ((wolf->error = place_player(wolf)))
		return (wolf->error);
	wolf->minimap.width = WIN_X_MINIMAP;
	wolf->minimap.height = WIN_Y_MINIMAP;
	wolf->radius = START_ANGLE;
	wolf->space_inter_radius = (double)FOV / (double)WIN_X;
	wolf->fisheyes = 0;
	wolf->mm_info.square = MINIMAP_ZOOM;
	wolf->mm_info.restx = fmod(wolf->minimap.width, wolf->mm_info.square);
	wolf->mm_info.resty = fmod(wolf->minimap.height, wolf->mm_info.square);
	wolf->mm_info.px = wolf->posx / MINIMAP_ZOOM;
	wolf->mm_info.py = wolf->posy / MINIMAP_ZOOM;
	wolf->mlx = mlx_init();
	init_textures(wolf);
	init_screen(wolf);
	return (0);
}
