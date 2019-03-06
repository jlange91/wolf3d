/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 03:56:00 by jlange            #+#    #+#             */
/*   Updated: 2019/03/06 05:56:06 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			choice_direction2(t_node *n, char dir, int *x, int *y)
{
	if (dir == 4 && n->x - 2 >= 0)
	{
		*x = n->x - 2;
		*y = n->y;
	}
	else if (dir == 4)
		return (1);
	if (dir == 8 && n->y - 2 >= 0)
	{
		*x = n->x;
		*y = n->y - 2;
	}
	else if (dir == 8)
		return (1);
	return (0);
}

int			choice_direction1(t_node *n, char dir, int *x, int *y)
{
	if (dir == 1 && n->x + 2 < SIZE_MAP)
	{
		*x = n->x + 2;
		*y = n->y;
	}
	else if (dir == 1)
		return (1);
	if (dir == 2 && n->y + 2 < SIZE_MAP)
	{
		*x = n->x;
		*y = n->y + 2;
	}
	else if (dir == 2)
		return (1);
	return (choice_direction2(n, dir, x, y));
}

t_node		*link_nodes(t_node *n, t_wolf *wolf, int x, int y)
{
	t_node	*dest;
	char	dir;

	if (n == NULL)
		return (NULL);
	while (n->dirs)
	{
		dir = (1 << (rand() % 4));
		if (~n->dirs & dir)
			continue ;
		n->dirs &= ~dir;
		if (choice_direction1(n, dir, &x, &y))
			continue ;
		dest = wolf->nodes + x + (y * SIZE_MAP);
		if (dest->c == ' ')
		{
			if (dest->parent != NULL)
				continue;
			dest->parent = n;
			wolf->nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2)
				* SIZE_MAP].c = ' ';
			return (dest);
		}
	}
	return (n->parent);
}

int			maze_generator(t_wolf *wolf)
{
	t_node	*start;
	t_node	*last;

	if (!(SIZE_MAP % 2))
		return (6);
	if (SIZE_MAP < 5)
		return (7);
	srand(time(NULL));
	if (init_maze(wolf, -1, -1))
	{
		wolf->error = 2;
		return (1);
	}
	start = wolf->nodes + 1 + SIZE_MAP;
	start->parent = start;
	last = start;
	while ((last = link_nodes(last, wolf, 0, 0)) != start)
		;
	fill_map(wolf);
	return (0);
}
