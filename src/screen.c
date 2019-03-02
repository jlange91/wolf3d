/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 01:43:42 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 01:44:24 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	display_column(t_wolf *wolf, int x, int y1, int y2, int test, double x1, double dist)
{
	unsigned int	color;
	int 			pixel;
	int 			i;

	i = 1;
	color = 0;
	if (y1 < 0)
	{
		i += abs(y1);
		y1 = 0;
	}
	while (y2 - y1 > 0 && y1 < WIN_Y)
	{
		pixel = (round(i / wolf->hpp) * wolf->text[test].width) +
			(fmod(x1, 1) * wolf->text[test].width);
		if (pixel >= 0 && pixel <
				(wolf->text[test].height * wolf->text[test].width) - 1)
			color = wolf->text[test].img[pixel];
		color = set_color(dist, color);
		pixel = (y1 * WIN_X) + x;
		if ((x >= 0 && x < WIN_X))
			wolf->screen.img[pixel] = color;
		++y1;
		++i;
	}
}

void					display_screen(t_wolf *wolf)
{
	wolf->screen.mlx_img = mlx_new_image(wolf->mlx, WIN_X, WIN_Y);
	wolf->screen.img = (unsigned int *)mlx_get_data_addr(wolf->screen.mlx_img,
			&wolf->screen.bpp, &wolf->screen.size_l, &wolf->screen.endian);
	wolf->screen.width = WIN_X;
	wolf->screen.height = WIN_Y;

	t_point point1;
	t_point point2;

	for (int i = 0; i < WIN_X; i++){
		point1.x = i;
		point2.x = i;
		point1.y = (WIN_Y / 2) - (wolf->inter[i].wall / 2);
		point2.y = (WIN_Y / 2) + (wolf->inter[i].wall / 2);
		if (wolf->inter[i].hit <= 0 || wolf->inter[i].hit > 4 || wolf->text[wolf->inter[i].hit - 1].mlx_img == NULL)
			ft_line_wall(point1, point2, &wolf->screen, set_color(wolf->inter[i].dist_wfe, wolf->inter[i].color));
		else
		{

			wolf->hpp = (double)wolf->inter[i].wall /
				(double)wolf->text[wolf->inter[i].hit - 1].height;

			display_column(wolf, i, point1.y, point2.y, wolf->inter[i].hit - 1,
					(wolf->inter[i].hit == 1 || wolf->inter[i].hit == 2) ? wolf->inter[i].point.x : wolf->inter[i].point.y, wolf->inter[i].dist_wfe);
		}
		floor_ceil_casting(wolf, &wolf->inter[i], i);

	}
	mlx_put_image_to_window(wolf->mlx, wolf->screen.win, wolf->screen.mlx_img, 0, 0);
	mlx_destroy_image(wolf->mlx, wolf->screen.mlx_img);
}

void init_screen(t_wolf *wolf)
{
	wolf->screen.win = mlx_new_window(wolf->mlx, WIN_X, WIN_Y, "Wolf3D");
	mlx_hook(wolf->screen.win, 2, (1L << 0), ft_display_hook, wolf);
	mlx_hook(wolf->screen.win, 17, (1L << 17), ft_redcross, wolf);
}
