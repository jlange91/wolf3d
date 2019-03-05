/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 22:32:51 by jlange            #+#    #+#             */
/*   Updated: 2019/03/05 03:05:48 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int						ft_display_hook(t_wolf *wolf)
{
	if (wolf->key[RIGHT])
	{
		wolf->radius = wolf->radius + (SPEED_ROT + wolf->key[SHIFT]);
		wolf->radius -= (wolf->radius >= 360.) ? 360 : 0;
	}
	if (wolf->key[LEFT])
	{
		wolf->radius = wolf->radius - (SPEED_ROT + wolf->key[SHIFT]);
		wolf->radius += (wolf->radius < 0.) ? 360 : 0;
	}
	if (wolf->key[UP])
		forward(wolf);
	if (wolf->key[DOWN])
		backward(wolf);
	return (0);
}
