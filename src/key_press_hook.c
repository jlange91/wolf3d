/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:44:05 by jlange            #+#    #+#             */
/*   Updated: 2019/03/05 14:44:33 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		key_press_hook(int keycode, t_wolf *wolf)
{
	if (keycode == ESC)
	{
		ft_free(wolf);
		exit(0);
	}
	else if (keycode == DIST_MINUS)
		wolf->length_view -= (wolf->length_view > 1) ? 1 : 0;
	else if (keycode == DIST_PLUS)
		wolf->length_view += (wolf->length_view < 1000000) ? 1 : 0;
	else if (keycode == FOV_MINUS)
		wolf->fov -= (wolf->fov > 10) ? 1 : 0;
	else if (keycode == FOV_PLUS)
		wolf->fov += (wolf->fov < 360) ? 1 : 0;
	else if (keycode == PLUS)
		wolf->mm_info.square += 1;
	else if (keycode == MINUS)
		wolf->mm_info.square -= (wolf->mm_info.square > 1) ? 1 : 0;
	wolf->key[keycode] = 1;
	return (0);
}
