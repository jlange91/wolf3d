/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:23:16 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:08:01 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void					display_minimap(t_wolf *wolf)
{
	t_point point_a;
	t_point point_b;

	wolf->mm_info.px = wolf->posX * MINIMAP_ZOOM;
	wolf->mm_info.py = wolf->posY * MINIMAP_ZOOM;
	wolf->minimap.mlx_img = mlx_new_image(wolf->mlx, wolf->minimap.width,
		wolf->minimap.height);
	wolf->minimap.img = (unsigned int *)mlx_get_data_addr(wolf->minimap.mlx_img,
		&wolf->minimap.bpb, &wolf->minimap.size_l, &wolf->minimap.endian);
	point_a.x = 0;
	point_a.y = 0;
	point_b.x = WIN_X_MINIMAP + 1;
	point_b.y = WIN_Y_MINIMAP + 1;
	ft_draw_rectangle(point_a, point_b, &wolf->minimap, 0xFF000000);
	minimap_draw_map(wolf);
	minimap_draw_angle(wolf);
	minimap_draw_perso(wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->screen.win, wolf->minimap.mlx_img,
			0, 0);
	mlx_destroy_image(wolf->mlx, wolf->minimap.img);
}
