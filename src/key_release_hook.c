#include "wolf3d.h"

int						key_release_hook(int keycode, t_wolf *wolf)
{
  wolf->key[keycode] = 0;
	if (keycode == FISHEYES)
		wolf->fisheyes = (wolf->fisheyes == 0) ? 1 : 0;
	return (0);
}
