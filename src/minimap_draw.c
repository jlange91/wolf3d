#include "wolf3d.h"

void 					minimap_draw_angle(t_wolf *wolf)
{
		int			i;
		t_point pointA;
		t_point pointB;

		i = -1;
		pointA.x = fmod(wolf->posX * MINIMAP_ZOOM, wolf->minimap.width);
		pointA.y = fmod(wolf->posY * MINIMAP_ZOOM, wolf->minimap.height);
		if (wolf->mm_info.px > wolf->minimap.width)
			pointA.x += wolf->mm_info.restx;
		if (wolf->mm_info.py > wolf->minimap.height)
			pointA.y += wolf->mm_info.resty;
		while (++i < WIN_X)
		{
			pointB = endpoint(wolf->inter[i].angle,
				fmod((wolf->posX * MINIMAP_ZOOM), wolf->minimap.width),
				fmod((wolf->posY * MINIMAP_ZOOM), wolf->minimap.height),
				wolf->inter[i].dist * MINIMAP_ZOOM);
			if (wolf->mm_info.px > wolf->minimap.width)
				pointB.x += wolf->mm_info.restx;
			if (wolf->mm_info.py > wolf->minimap.height)
				pointB.y += wolf->mm_info.resty;
			ft_line(pointA, pointB, &wolf->minimap, BLEU_F);
		}
}

void 					minimap_draw_map(t_wolf *wolf)
{
  t_point pointA;
  t_point pointB;
  int x;
  int y;
	int multX = ((wolf->posX * MINIMAP_ZOOM) / wolf->minimap.width);
	int multY = ((wolf->posY * MINIMAP_ZOOM) / wolf->minimap.height);

  y = 0;
  while (y < wolf->minimap.height / wolf->mm_info.square)
  {
    x = 0;
    while (x < wolf->minimap.width / wolf->mm_info.square)
    {
			int rx = x + ((wolf->minimap.width / wolf->mm_info.square) * multX);
			int ry = y + ((wolf->minimap.height / wolf->mm_info.square) * multY);
      if (ry < wolf->mapHeigth &&
				rx < wolf->mapWidth &&
				wolf->map[ry][rx])
      {
        pointA.x = x * wolf->mm_info.square;
        pointA.y = y * wolf->mm_info.square;
        pointB.x = (x + 1) * wolf->mm_info.square;
        pointB.y = (y + 1) * wolf->mm_info.square;
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
  int 		y;
	int 		x;

  y = 0;
	x = 0;
  while (y < wolf->minimap.height / wolf->mm_info.square)
  {
				pointA.x = 0;
				pointA.y = y * wolf->mm_info.square - 1;
				pointB.x = wolf->minimap.width - 1;
				pointB.y = y * wolf->mm_info.square - 1;
				ft_line(pointA, pointB, &wolf->minimap, BLANC);
    ++y;
  }
	while (x < wolf->minimap.width / wolf->mm_info.square)
	{
				pointA.x = x * wolf->mm_info.square - 1;
				pointA.y = 0;
				pointB.x = x * wolf->mm_info.square - 1;
				pointB.y = wolf->minimap.height - 1;
				ft_line(pointA, pointB, &wolf->minimap, BLANC);
		++x;
	}
}

void 					minimap_draw_perso(t_wolf *wolf)
{
	t_point pointA;
	t_point pointB;

	pointA.x = fmod(wolf->mm_info.px, wolf->minimap.width) - 1;
	pointA.y = fmod(wolf->mm_info.py, wolf->minimap.height) - 1;
	pointB.x = fmod(wolf->mm_info.px, wolf->minimap.width) + 1;
	pointB.y = fmod(wolf->mm_info.py, wolf->minimap.height) + 1;
	if (wolf->mm_info.px > wolf->minimap.width)
	{
		pointA.x += wolf->mm_info.restx;
		pointB.x += wolf->mm_info.restx;
	}
	if (wolf->mm_info.py > wolf->minimap.height)
	{
		pointA.y += wolf->mm_info.resty;
		pointB.y += wolf->mm_info.resty;
	}
	ft_draw_rectangle(pointA, pointB, &wolf->minimap, 0x00FF0000);
}
