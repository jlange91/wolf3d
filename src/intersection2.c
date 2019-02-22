#include "wolf3d.h"

t_dpoint find_dist(double angle)
{
	double xA;
	double yA;
	t_dpoint dist;

	xA = fabs(1 / d_tan(angle));
	yA = fabs(1 * d_tan(angle));
	dist.x = sqrt(xA * xA + 1);
	dist.y = sqrt(yA * yA + 1);
	return (dist);
}

t_dpoint find_first_dist(double posX, double posY, double angle)
{
	double x;
	double y;
	double xA;
	double yA;
	t_dpoint dist;

	x = (angle > 90 && angle < 270) ? fabs(fmod(posX, 1)) :
																		fabs(fmod(posX, 1) - 1);
	y = (angle > 180) ? fabs(fmod(posY, 1)) :
											fabs(fmod(posY, 1) - 1);
	xA = fabs(y / d_tan(angle));
	yA = fabs(x * d_tan(angle));
	dist.x = sqrt(xA * xA + y * y);
	dist.y = sqrt(yA * yA + x * x);
	return (dist);
}

t_intersection search_intersection(t_wolf *wolf, t_intersection inter)
{
	t_dpoint	dist = find_dist(inter.angle);
	t_dpoint	first_dist = find_first_dist(wolf->posX, wolf->posY, inter.angle);
	int stepX;
	int stepY;

	if (inter.angle > 90 && inter.angle < 270)
		stepX = -1;
	else
		stepX = 1;
	if (inter.angle > 180)
		stepY = -1;
	else
		stepY = 1;

	int mapX = (int)wolf->posX;
	int mapY = (int)wolf->posY;
	int hit = 0;

	while (hit == 0)
	{
		if (first_dist.x < first_dist.y || first_dist.y == INFINITY)
		{
			if (first_dist.x >= LENGHT_VIEW)
				break ;
      inter.dist = first_dist.x;
      inter.hit = (inter.angle > 180) ? 1 : 2;
			first_dist.x += dist.x;
			mapY += stepY;
			mapY = ret_uchar(mapY);
		}
		else
		{
			if (first_dist.y >= LENGHT_VIEW)
				break ;
      inter.dist = first_dist.y;
      inter.hit = (inter.angle > 90 && inter.angle < 270) ? 3 : 4;
			first_dist.y += dist.y;
			mapX += stepX;
			mapX = ret_uchar(mapX);
		}
		if ((mapX >= 0 && mapX < wolf->mapWidth) &&
				(mapY >= 0 && mapY < wolf->mapHeigth) &&
				wolf->map[mapY][mapX] > 0)
			hit = 1;
	}

	if (hit == 0)
  {
    inter.dist = LENGHT_VIEW;
    inter.hit = 0;
  }
	if (inter.hit == 0)
		inter.color = 0;
	else if (inter.hit == 1)
		inter.color = BLEU_C;
	else if (inter.hit == 2)
		inter.color = VERT_C;
	else if (inter.hit == 3)
		inter.color = JAUNE;
	else if (inter.hit == 4)
		inter.color = BLANC;
	inter.point = endpoint2(inter.angle, wolf->posX, wolf->posY, inter.dist);

	if (!wolf->fisheyes)
	{
		double middle = wolf->radius + (FOV / 2);
		double angle = (inter.angle < wolf->radius) ? inter.angle + 360 : inter.angle;
		double diff = (middle > angle) ? angle - middle : middle - angle;
		inter.dist_wfe = inter.dist * d_cos(diff);
	}
	else
		inter.dist_wfe = inter.dist;
  return (inter);
}
