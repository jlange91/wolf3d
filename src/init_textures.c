/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:05:32 by jlange            #+#    #+#             */
/*   Updated: 2019/03/06 00:32:12 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_textures(t_wolf *wolf)
{
	char	*str[7];
	int		i;

	i = -1;
	str[0] = "texture/wall1.xpm";
	str[1] = "texture/wall2.xpm";
	str[2] = "texture/wall3.xpm";
	str[3] = "texture/wall4.xpm";
	str[4] = "texture/floor.xpm";
	str[5] = "texture/ceil.xpm";
	str[6] = "texture/win.xpm";
	while (++i < 7)
	{
		wolf->text[i].mlx_img = mlx_xpm_file_to_image(wolf->mlx, str[i],
				&wolf->text[i].width, &wolf->text[i].height);
		if (!wolf->text[i].mlx_img)
		{
			ft_putstr_fd("Warning: Missing file ", 2);
			ft_putendl_fd(str[i], 2);
		}
		else
			wolf->text[i].img = (unsigned int *)mlx_get_data_addr(
					wolf->text[i].mlx_img, &wolf->text[i].bpp,
					&wolf->text[i].size_l, &wolf->text[i].endian);
	}
}
