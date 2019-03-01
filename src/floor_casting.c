#include "wolf3d.h"

static inline void ceil_casting(t_wolf *wolf, t_fc c, int x) {
  unsigned int  color;
  int           pixel;

  color = 0;
  if (wolf->text[5].mlx_img != NULL)
  {
    c.floorTexX = (int)(c.currentFloorX * wolf->text[5].width) % wolf->text[5].width;
    c.floorTexY = (int)(c.currentFloorY * wolf->text[5].height) % wolf->text[5].height;
    pixel = (c.floorTexY * wolf->text[5].width) + c.floorTexX;
    if (pixel >= 0 && pixel < (wolf->text[5].height * wolf->text[5].width) - 1)
      color = wolf->text[5].img[pixel];
  }
  else
    color = BLEU_C;
  color = set_color(c.currentDist, color);
  pixel = ((WIN_Y - c.y) * WIN_X) + x;
  if (pixel >= 0 && pixel < (wolf->screen.height * wolf->screen.width) - 1)
    wolf->screen.img[pixel] = color;
}

static inline void floor_casting(t_wolf *wolf, t_fc c, int x) {
  unsigned int  color;
  int           pixel;

  color = 0;
  if (wolf->text[4].mlx_img != NULL)
  {
    c.floorTexX = (int)(c.currentFloorX * wolf->text[4].width) % wolf->text[4].width;
    c.floorTexY = (int)(c.currentFloorY * wolf->text[4].height) % wolf->text[4].height;
    pixel = (c.floorTexY * wolf->text[4].width) + c.floorTexX;
    if (pixel >= 0 && pixel < (wolf->text[4].height * wolf->text[4].width) - 1)
      color = wolf->text[4].img[pixel];
  }
  else
    color = MARON_F;
  color = set_color(c.currentDist, color);
  pixel = (c.y * WIN_X) + x;
  if (pixel >= 0 && pixel < (wolf->screen.height * wolf->screen.width) - 1)
    wolf->screen.img[pixel] = color;
}

void floor_ceil_casting(t_wolf *wolf, t_intersection *inter, int x)
{
  t_fc c;

	c.drawEnd = (WIN_Y / 2) + (inter->wall / 2);
  if (c.drawEnd < 0)
    c.drawEnd = WIN_Y;
	c.floorXWall = inter->point.x;
	c.floorYWall = inter->point.y;
	c.distWall = inter->dist_wfe;
  c.y = c.drawEnd + 1;
	while (c.y < WIN_Y)
	{
		c.currentDist = WIN_Y / (2.0 * c.y - WIN_Y);
		c.weight = c.currentDist / c.distWall;
		c.currentFloorX = resize_double(c.weight * c.floorXWall +
       (1.0 - c.weight) * wolf->posX);
		c.currentFloorY = resize_double(c.weight * c.floorYWall +
       (1.0 - c.weight) * wolf->posY);
     floor_casting(wolf, c, x);
     ceil_casting(wolf, c, x);
    c.y++;
	}
}
