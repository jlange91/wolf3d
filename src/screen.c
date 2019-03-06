/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 01:43:42 by jlange            #+#    #+#             */
/*   Updated: 2019/03/03 01:44:24 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void					init_display_column(t_wolf *wolf, int x, t_dc *c)
{
	c->text = (wolf->inter[x].win == 1) ? 6 : wolf->inter[x].hit - 1;
	wolf->hpp = (double)wolf->inter[x].wall
				/ (double)wolf->text[c->text].height;
	c->x1 = (wolf->inter[x].hit == 1 || wolf->inter[x].hit == 2)
		? wolf->inter[x].point.x : wolf->inter[x].point.y;
	c->dist = wolf->inter[x].dist_wfe;
	c->i = 0;
	c->color = 0;
}

void					display_column(t_wolf *wolf, int x, int y1, int y2)
{
	t_dc c;

	init_display_column(wolf, x, &c);
	if (y1 < 0)
	{
		c.i += abs(y1);
		y1 = 0;
	}
	while (y2 - y1 > 0 && y1 < WIN_Y)
	{
		c.pixel = (round(c.i / wolf->hpp) * wolf->text[c.text].width)
			+ (fmod(c.x1, 1) * wolf->text[c.text].width);
		if (c.pixel >= 0 && c.pixel
				< (wolf->text[c.text].height * wolf->text[c.text].width) - 1)
			c.color = wolf->text[c.text].img[c.pixel];
		c.color = set_color(c.dist, c.color, wolf->length_view);
		c.pixel = (y1 * WIN_X) + x;
		if ((x >= 0 && x < WIN_X))
			wolf->screen.img[c.pixel] = c.color;
		++y1;
		++c.i;
	}
}

static inline void		display_screen_loop(t_wolf *wolf)
{
	t_point		point1;
	t_point		point2;
	int			x;

	x = -1;
	while (++x < WIN_X)
	{
		point1.x = x;
		point2.x = x;
		point1.y = (WIN_Y / 2) - (wolf->inter[x].wall / 2);
		point2.y = (WIN_Y / 2) + (wolf->inter[x].wall / 2);
		if (wolf->inter[x].hit <= 0 || wolf->inter[x].hit > 4
				|| wolf->text[wolf->inter[x].hit - 1].mlx_img == NULL
			|| (wolf->inter[x].win == 1 && wolf->text[6].mlx_img == NULL))
			ft_line_wall(point1, point2, &wolf->screen,
					set_color(wolf->inter[x].dist_wfe, wolf->inter[x].color,
						wolf->length_view));
		else
			display_column(wolf, x, point1.y, point2.y);
		floor_ceil_casting(wolf, &wolf->inter[x], x);
	}
}

void					display_screen(t_wolf *wolf)
{
	wolf->screen.mlx_img = mlx_new_image(wolf->mlx, WIN_X, WIN_Y);
	wolf->screen.img = (unsigned int *)mlx_get_data_addr(wolf->screen.mlx_img,
			&wolf->screen.bpp, &wolf->screen.size_l, &wolf->screen.endian);
	wolf->screen.width = WIN_X;
	wolf->screen.height = WIN_Y;
	display_screen_loop(wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->screen.win,
			wolf->screen.mlx_img, 0, 0);
	mlx_destroy_image(wolf->mlx, wolf->screen.mlx_img);
}
