#include "wolf3d.h"

unsigned int	set_color(double dist, unsigned int color)
{
	unsigned int coef;
	unsigned int red;
	unsigned int green;
	unsigned int blue;

	coef = dist * 100 / LENGHT_VIEW;
	red = ((color & 0xFF0000) >> 16) * (100 - coef) / 100;
	red = (red > 0xFF) ? 0 : red;
	green = ((color & 0xFF00) >> 8) * (100 - coef) / 100;
	green = (green > 0xFF) ? 0 : green;
	blue = ((color & 0xFF)) * (100 - coef) / 100;
	blue = (blue > 0xFF) ? 0 : blue;
	color = (red << 16) + (color & 0x00FFFF);
	color = (green << 8) + (color & 0xFF00FF);
	color = blue + (color & 0xFFFF00);
	return (color);
}

void	display_column(t_wolf *wolf, int x, int y1, int y2, int test, double x1, double dist)
{
	unsigned int	color = 0;
	int 					pixel;
	int 					i;

	i = 1;
	if (y1 < 0)
	{
		i += abs(y1);
		y1 = 0;
	}
	while (y2 - y1 > 0 && y1 < WIN_Y)
	{
		pixel = (round(i / wolf->hpp) * wolf->wall[test].width) + (fmod(x1, 1) * wolf->wall[test].width);
		if (pixel >= 0 && pixel < (wolf->wall[test].height * wolf->wall[test].width) - 1)
			color = wolf->wall[test].img[pixel];
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

	// for (int i = 0; i < WIN_X; i++){
	// 	point1.x = i;
	// 	point2.x = i;
	// 	point1.y = (WIN_Y / 2);
	// 	point2.y = WIN_Y;
	// 		ft_line_wall(point1, point2, &wolf->screen, BLANC);
	// 	}
	//
	// 	for (int i = 0; i < WIN_X; i++){
	// 		point1.x = i;
	// 		point2.x = i;
	// 		point1.y = 0;
	// 		point2.y = WIN_Y / 2;
	// 			ft_line_wall(point1, point2, &wolf->screen, BLEU_C);
	// 		}

  for (int i = 0; i < WIN_X; i++){
    point1.x = i;
    point2.x = i;
    point1.y = (WIN_Y / 2) - (wolf->inter[i].wall / 2);
    point2.y = (WIN_Y / 2) + (wolf->inter[i].wall / 2);
    if (wolf->inter[i].hit <= 0 || wolf->inter[i].hit > 4 || wolf->wall[wolf->inter[i].hit - 1].mlx_img == NULL)
			ft_line_wall(point1, point2, &wolf->screen, set_color(wolf->inter[i].dist_wfe, wolf->inter[i].color));
    else
		{

			wolf->hpp = (double)wolf->inter[i].wall /
									(double)wolf->wall[wolf->inter[i].hit - 1].height;

			display_column(wolf, i, point1.y, point2.y, wolf->inter[i].hit - 1,
				(wolf->inter[i].hit == 1 || wolf->inter[i].hit == 2) ? wolf->inter[i].point.x : wolf->inter[i].point.y, wolf->inter[i].dist_wfe);
		}
  }


	mlx_put_image_to_window(wolf->mlx, wolf->screen.win, wolf->screen.mlx_img, 0, 0);
	mlx_destroy_image(wolf->mlx, wolf->screen.mlx_img);
}

void init_screen(t_wolf *wolf)
{
	wolf->screen.win = mlx_new_window(wolf->mlx, WIN_X, WIN_Y, "screen");
	mlx_hook(wolf->screen.win, 2, (1L << 0), ft_display_hook, wolf);
	mlx_hook(wolf->screen.win, 17, (1L << 17), ft_redcross, wolf);
}
