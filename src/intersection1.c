#include "wolf3d.h"

void  search_intersections(t_wolf *wolf)
{
	t_point map0;
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
		wolf->inter[i].wall = WIN_Y / wolf->inter[i].dist_wfe;
		// printf("%f\n", wolf->inter[i].dist_wfe);
		startAngle += wolf->spaceInterRadius;
		startAngle -= (startAngle >= 360.) ? 360 : 0;
		++i;
	}
}
