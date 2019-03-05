/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:43:35 by jlange            #+#    #+#             */
/*   Updated: 2019/03/05 14:43:48 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int						key_release_hook(int keycode, t_wolf *wolf)
{
	wolf->key[keycode] = 0;
	if (keycode == FISHEYES)
		wolf->fisheyes = (wolf->fisheyes == 0) ? 1 : 0;
	return (0);
}
