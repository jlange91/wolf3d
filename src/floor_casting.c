/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 00:25:45 by jlange            #+#    #+#             */
/*   Updated: 2019/03/03 02:03:11 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void	ceil_casting(t_wolf *wolf, t_fc c, int x)
{
	unsigned int	color;
	int				pixel;

	color = 0;
	if (wolf->text[5].mlx_img != NULL)
	{
		c.floor_tex_x = (int)(c.current_floor_x * wolf->text[5].width)
			% wolf->text[5].width;
		c.floor_tex_y = (int)(c.current_floor_y * wolf->text[5].height)
			% wolf->text[5].height;
		pixel = (c.floor_tex_y * wolf->text[5].width) + c.floor_tex_x;
		if (pixel >= 0 && pixel < (wolf->text[5].height
					* wolf->text[5].width) - 1)
			color = wolf->text[5].img[pixel];
	}
	else
		color = BLEU_C;
	color = set_color(c.current_dist, color, wolf->length_view);
	pixel = ((WIN_Y - c.y) * WIN_X) + x;
	if (pixel >= 0 && pixel < (wolf->screen.height * wolf->screen.width) - 1)
		wolf->screen.img[pixel] = color;
}

static inline void	floor_casting(t_wolf *wolf, t_fc c, int x)
{
	unsigned int	color;
	int				pixel;

	color = 0;
	if (wolf->text[4].mlx_img != NULL)
	{
		c.floor_tex_x = (int)(c.current_floor_x * wolf->text[4].width)
			% wolf->text[4].width;
		c.floor_tex_y = (int)(c.current_floor_y * wolf->text[4].height)
			% wolf->text[4].height;
		pixel = (c.floor_tex_y * wolf->text[4].width) + c.floor_tex_x;
		if (pixel >= 0 && pixel < (wolf->text[4].height
					* wolf->text[4].width) - 1)
			color = wolf->text[4].img[pixel];
	}
	else
		color = MARON_F;
	color = set_color(c.current_dist, color, wolf->length_view);
	pixel = (c.y * WIN_X) + x;
	if (pixel >= 0 && pixel < (wolf->screen.height * wolf->screen.width) - 1)
		wolf->screen.img[pixel] = color;
}

void				floor_ceil_casting(t_wolf *wolf, t_intersection *inter,
		int x)
{
	t_fc c;

	c.drawend = (WIN_Y / 2) + (inter->wall / 2);
	if (c.drawend < 0)
		c.drawend = WIN_Y;
	c.floor_x_wall = inter->point.x;
	c.floor_y_wall = inter->point.y;
	c.dist_wall = inter->dist_wfe;
	c.y = c.drawend;
	while (c.y < WIN_Y)
	{
		c.current_dist = WIN_Y / (2.0 * c.y - WIN_Y);
		c.weight = c.current_dist / c.dist_wall;
		c.current_floor_x = resize_double(c.weight * c.floor_x_wall
				+ (1.0 - c.weight) * wolf->posx);
		c.current_floor_y = resize_double(c.weight * c.floor_y_wall
				+ (1.0 - c.weight) * wolf->posy);
		floor_casting(wolf, c, x);
		ceil_casting(wolf, c, x);
		c.y++;
	}
}
