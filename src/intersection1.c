/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 00:42:31 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 00:43:17 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	search_intersections(t_wolf *wolf)
{
	t_point		map0;
	double		start_angle;
	int			i;

	i = 0;
	map0.x = wolf->posX;
	map0.y = wolf->posY;
	start_angle = wolf->radius;
	while (i < WIN_X)
	{
		wolf->inter[i].angle = start_angle;
		wolf->inter[i] = search_intersection(wolf, wolf->inter[i]);
		wolf->inter[i].wall = WIN_Y / wolf->inter[i].dist_wfe;
		start_angle += wolf->spaceInterRadius;
		start_angle -= (start_angle >= 360.) ? 360 : 0;
		++i;
	}
}
