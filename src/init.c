/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:04:57 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:05:09 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <time.h>

static int		place_player(t_wolf *wolf)
{
	int y;
	int x;

	y = 0;
	while (y < wolf->mapHeigth)
	{
		x = 0;
		while (x < wolf->mapWidth)
		{
			if (wolf->map[y][x] == 0)
			{
				wolf->posX = x + 0.5;
				wolf->posY = y + 0.5;
				return (0);
			}
			++x;
		}
		++y;
	}
	return (5);
}

unsigned int 		**create_map(t_wolf *wolf) {
	unsigned int	**ret;
	int	i;
	int	j;

	i = 0;
	srand(time(NULL));
	ret = (unsigned int**)malloc(sizeof(unsigned int*) * SIZE_INFINY_MAP);
	while (i < SIZE_INFINY_MAP)
	{
		j = 0;
		ret[i] = (unsigned int*)malloc(sizeof(unsigned int) * SIZE_INFINY_MAP);
		while (j < SIZE_INFINY_MAP)
		{
			// if (i == 0 || i == 299 || j == 0 || j == 299)
			// 	ret[i][j] = 1;
			// else
				ret[i][j] = ((rand() % 100) > BLOCKS_PERCENT) ? 1 : 0;
			++j;
		}
		++i;
	}
	wolf->mapWidth = SIZE_INFINY_MAP;
	wolf->mapHeigth = SIZE_INFINY_MAP;
	return (ret);
}

int				ft_init(t_wolf *wolf, int ac, char **av)
{
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
	wolf->spaceInterRadius = (double)FOV / (double)WIN_X;
	wolf->fisheyes = 0;
	wolf->mm_info.square = MINIMAP_ZOOM;
	wolf->mm_info.restx = fmod(wolf->minimap.width, wolf->mm_info.square);
	wolf->mm_info.resty = fmod(wolf->minimap.height, wolf->mm_info.square);
	wolf->mm_info.px = wolf->posX / MINIMAP_ZOOM;
	wolf->mm_info.py = wolf->posY / MINIMAP_ZOOM;
	wolf->mlx = mlx_init();
	init_textures(wolf);
	init_screen(wolf);
	return (0);
}
