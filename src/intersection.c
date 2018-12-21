#include "wolf3d.h"

t_dpoint find_dist(double angle)
{
	double xA;
	double yA;
	t_dpoint dist;

	xA = fabs(SQUARE / dTan(angle));
	yA = fabs(SQUARE * dTan(angle));
	dist.x = sqrt(xA * xA + SQUARE * SQUARE);
	dist.y = sqrt(yA * yA + SQUARE * SQUARE);
/*	if (angle == 0 || angle == 180)
	{
		dist.y = SQUARE;
		dist.x = INFINITY;
	}
	else if (angle == 90 || angle == 270)
	{
			dist.x = SQUARE;
			dist.y = INFINITY;
	}*/
	return (dist);
}

t_dpoint find_first_dist(double posX, double posY, double angle)
{
	double x;
	double y;
	double xA;
	double yA;
	t_dpoint dist;

	x = (angle > 90 && angle < 270) ? fabs(fmod(posX, SQUARE)) :
																		fabs(fmod(posX, SQUARE) - SQUARE);
	y = (angle > 180) ? fabs(fmod(posY, SQUARE)) :
											fabs(fmod(posY, SQUARE) - SQUARE);
	xA = fabs(y / dTan(angle));
	yA = fabs(x * dTan(angle));
	dist.x = sqrt(xA * xA + y * y);
	dist.y = sqrt(yA * yA + x * x);
/*	if (angle == 0 || angle == 180)
	{
		dist.y = y;
		dist.x = INFINITY;
	}
	else if (angle == 90 || angle == 270)
	{
		dist.x = x;
		dist.y = INFINITY;
	}*/
	return (dist);
}

t_intersection search_intersection(t_wolf *wolf, t_intersection inter)
{
	t_dpoint	dist = find_dist(inter.angle);
	t_dpoint	first_dist = find_first_dist(wolf->posX, wolf->posY, inter.angle);
	int stepX;
	int stepY;

	int currentX = (wolf->posX / SQUARE) * SQUARE;
	int currentY = (wolf->posY / SQUARE) * SQUARE;

	if (inter.angle > 90 && inter.angle < 270)
		stepX = -1;
	else
		stepX = 1;
	if (inter.angle > 180)
		stepY = -1;
	else
		stepY = 1;

	int mapX = (wolf->posX / SQUARE);
	int mapY = (wolf->posY / SQUARE);
	int firstx = 0;
	int firsty = 0;
	int side = 0;
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
		}
		else
		{
			if (first_dist.y >= LENGHT_VIEW)
				break ;
      inter.dist = first_dist.y;
      inter.hit = (inter.angle > 90 && inter.angle < 270) ? 3 : 4;
			first_dist.y += dist.y;
			mapX += stepX;
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
	inter.point = endpoint(inter.angle, wolf->posX, wolf->posY, inter.dist);

	if (!wolf->fisheyes)
	{
		double middle = wolf->radius + (FOV / 2);
		double angle = (inter.angle < wolf->radius) ? inter.angle + 360 : inter.angle;
		double diff = (middle > angle) ? angle - middle : middle - angle;
		inter.dist_wfe = inter.dist * dCos(diff);
	}
	else
		inter.dist_wfe = inter.dist;
  return (inter);
}


void  search_intersections(t_wolf *wolf)
{
	t_point map0;
	t_point map1;
	double	startAngle;
	int			i;

	i = 0;
	map0.x = wolf->posX;
	map0.y = wolf->posY;
	startAngle = wolf->radius;
	while (i < WIN_X)
	{
    wolf->inter[i].angle = startAngle;
		wolf->inter[i] = search_intersection(wolf, wolf->inter[i]);
		wolf->inter[i].wall = ((WIN_X / 2) / dTan(30) * SQUARE) / wolf->inter[i].dist_wfe;
		startAngle += wolf->spaceInterRadius;
		startAngle -= (startAngle >= 360.) ? 360 : 0;
		++i;
	}
}
