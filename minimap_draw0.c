#include "wolf3d.h"

void 					minimap_draw_angle(t_wolf *wolf)
{
		int			i;
		t_point point1;
		t_point point2;

		i = -1;
		point1.x = fmod(wolf->posX, WIN_X_MINIMAP);
		point1.y = fmod(wolf->posY, WIN_Y_MINIMAP);
		while (++i < WIN_X)
			ft_line(point1, wolf->inter[i].point, &wolf->minimap, BLEU_F);
}

void 					minimap_draw_map(t_wolf *wolf)
{
  t_point pointA;
  t_point pointB;
  int x;
  int y;
	int multX = (wolf->posX / WIN_X_MINIMAP);
	int multY = (wolf->posY / WIN_Y_MINIMAP);

  y = 0;
  while (y < WIN_Y_MINIMAP / SQUARE)
  {
    x = 0;
    while (x < WIN_Y_MINIMAP / SQUARE)
    {
			int rx = x + ((WIN_X_MINIMAP / SQUARE) * multX);
			int ry = y + ((WIN_Y_MINIMAP / SQUARE) * multY);
      if (ry < wolf->mapHeigth &&
				rx < wolf->mapWidth &&
				wolf->map[ry][rx])
      {
        pointA.x = x * SQUARE;
        pointA.y = y * SQUARE;
        pointB.x = (x + 1) * SQUARE;
        pointB.y = (y + 1) * SQUARE;
        ft_draw_rectangle(pointA, pointB, &wolf->minimap, BLANC);
      }
      ++x;
    }
    ++y;
  }
}

void 					minimap_draw_cadriage(t_wolf *wolf)
{
  t_point pointA;
  t_point pointB;
  int y;
	int x;

  y = 0;
	x = 0;
  while (y < WIN_Y_MINIMAP / SQUARE)
  {
				pointA.x = 0;
				pointA.y = y * SQUARE - 1;
				pointB.x = WIN_X_MINIMAP - 1;
				pointB.y = y * SQUARE - 1;
				ft_line(pointA, pointB, &wolf->minimap, BLANC);
    ++y;
  }
	while (x < WIN_X_MINIMAP / SQUARE)
	{
				pointA.x = x * SQUARE - 1;
				pointA.y = 0;
				pointB.x = x * SQUARE - 1;
				pointB.y = WIN_Y_MINIMAP - 1;
				ft_line(pointA, pointB, &wolf->minimap, BLANC);
		++x;
	}
}

void 					minimap_draw_perso(t_wolf *wolf)
{
	t_point pointA;
	t_point pointB;

	pointA.x = fmod(wolf->posX, 480) - 2;
	pointA.y = fmod(wolf->posY, 480) - 2;
	pointB.x = fmod(wolf->posX, 480) + 2;
	pointB.y = fmod(wolf->posY, 480) + 2;
	ft_draw_rectangle(pointA, pointB, &wolf->minimap, 0x00FF0000);
}
