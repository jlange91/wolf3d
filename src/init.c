/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:04:57 by jlange            #+#    #+#             */
/*   Updated: 2019/03/05 02:43:45 by jlange           ###   ########.fr       */
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

int				create_map(t_wolf *wolf)
{
	int		i;
	int		j;

	i = 0;
	srand(time(NULL));
	if (!(wolf->map = (t_map**)malloc(sizeof(t_map*) * SIZE_INFINY_MAP)))
		return (2);
	while (i < SIZE_INFINY_MAP)
	{
		j = -1;
		if (!(wolf->map[i] = (t_map*)malloc(sizeof(t_map) * SIZE_INFINY_MAP)))
			return (2);
		while (++j < SIZE_INFINY_MAP)
		{
			wolf->map[i][j].type = ((rand() % 100) > BLOCKS_PERCENT) ? 1 : 0;
			wolf->map[i][j].discover = DISCOVER;
		}
		++i;
	}
	wolf->map_width = SIZE_INFINY_MAP;
	wolf->map_height = SIZE_INFINY_MAP;
	return (0);
}

void 			init_key(t_wolf *wolf)
{
	int i;

	i = -1;
	while (++i < 280)
		wolf->key[i] = 0;
}

int				ft_init(t_wolf *wolf, int ac, char **av)
{
	if ((wolf->error = (ac > 1) ? ft_fill_tab(wolf, av) : create_map(wolf)))
		return (wolf->error);
	if ((wolf->error = place_player(wolf)))
		return (wolf->error);
	wolf->length_view = LENGTH_VIEW;
	wolf->fov = FOV;
	wolf->minimap.width = WIN_X_MINIMAP;
	wolf->minimap.height = WIN_Y_MINIMAP;
	wolf->radius = START_ANGLE;
	wolf->fisheyes = 0;
	wolf->mm_info.square = MINIMAP_ZOOM;
	wolf->mm_info.restx = fmod(wolf->minimap.width, wolf->mm_info.square);
	wolf->mm_info.resty = fmod(wolf->minimap.height, wolf->mm_info.square);
	wolf->mm_info.px = wolf->posx / MINIMAP_ZOOM;
	wolf->mm_info.py = wolf->posy / MINIMAP_ZOOM;
	wolf->mlx = mlx_init();
	wolf->screen.win = mlx_new_window(wolf->mlx, WIN_X, WIN_Y, "Wolf3D");
	init_textures(wolf);
	init_key(wolf);
	return (0);
}
