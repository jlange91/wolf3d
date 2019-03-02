/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:04:30 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:04:39 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_free(t_wolf *wolf)
{
	int y;

	y = 0;
	while (wolf->map && y < wolf->map_height)
	{
		if (wolf->map[y])
			free(wolf->map[y]);
		++y;
	}
	if (wolf->map)
		free(wolf->map);
	y = 0;
	while (wolf->error == 0 && y < 6)
	{
		if (wolf->text[y].mlx_img)
			mlx_destroy_image(wolf->mlx, wolf->text[y].mlx_img);
		++y;
	}
}
