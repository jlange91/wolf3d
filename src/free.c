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
	while (y < wolf->mapHeigth)
	{
		free(wolf->map[y]);
		++y;
	}
	free(wolf->map);
	y = 0;
	while (y < 4)
	{
		if (wolf->text[y].mlx_img)
			mlx_destroy_image(wolf->mlx, wolf->text[y].mlx_img);
		++y;
	}
}
