#include "wolf3d.h"

static int    place_player(t_wolf *wolf)
{
  int y;
  int x;

  y = 0;
  while (y < wolf->mapHeigth)
  {
    x = 0;
    while (x < wolf->mapWidth)
    {
      if (wolf->map[y][x] == 0)
      {
        wolf->posX = x + 0.5;
        wolf->posY = y + 0.5;
        return (0);
      }
      ++x;
    }
    ++y;
  }
  return (5);
}

int    ft_init(t_wolf *wolf, char **av)
{
  if ((wolf->error = ft_fill_tab(wolf, av)))
    return (wolf->error);
  if ((wolf->error = place_player(wolf)))
    return (wolf->error);
  wolf->minimap.width = WIN_X_MINIMAP;
  wolf->minimap.height = WIN_Y_MINIMAP;
  wolf->radius = START_ANGLE;
  wolf->spaceInterRadius = (double)FOV / (double)WIN_X;
  wolf->fisheyes = 0;
  wolf->mm_info.square = MINIMAP_ZOOM;
  wolf->mm_info.restx = fmod(wolf->minimap.width, wolf->mm_info.square);
  wolf->mm_info.resty = fmod(wolf->minimap.height, wolf->mm_info.square);
  wolf->mm_info.px = wolf->posX / MINIMAP_ZOOM;
  wolf->mm_info.py = wolf->posY / MINIMAP_ZOOM;
  wolf->mlx = mlx_init();
  init_textures(wolf);
  init_screen(wolf);
  return (0);
}
