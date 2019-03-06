/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_maze.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 05:53:25 by jlange            #+#    #+#             */
/*   Updated: 2019/03/06 05:53:30 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
