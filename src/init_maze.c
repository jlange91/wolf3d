/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_maze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:53:25 by jlange            #+#    #+#             */
/*   Updated: 2019/03/06 06:48:23 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_map(t_wolf *wolf)
{
	short	alea;
	int		i;
	int		j;

	alea = (rand() % 4);
	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
			wolf->map[i][j].type = (wolf->nodes[j + i * SIZE_MAP].c == '#')
				? 1 : 0;
	}
	if (alea == 0)
		wolf->map[1][1].win = 1;
	else if (alea == 1)
		wolf->map[1][SIZE_MAP - 2].win = 1;
	else if (alea == 2)
		wolf->map[SIZE_MAP - 2][1].win = 1;
	else if (alea == 3)
		wolf->map[SIZE_MAP - 2][SIZE_MAP - 2].win = 1;
	wolf->map_height = SIZE_MAP;
	wolf->map_width = SIZE_MAP;
}

int		init_maze(t_wolf *wolf, int i, int j)
{
	t_node *n;

	if (!(wolf->nodes = (t_node*)malloc(sizeof(t_node)
					* (SIZE_MAP * SIZE_MAP))))
		return (1);
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
		{
			n = wolf->nodes + i + j * SIZE_MAP;
			if (i * j % 2)
			{
				n->x = i;
				n->y = j;
				n->dirs = 0b1111;
				n->c = ' ';
				n->parent = NULL;
			}
			else
				n->c = '#';
		}
	}
	return (0);
}
