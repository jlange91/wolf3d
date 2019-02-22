/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:05:32 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:06:10 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_textures(t_wolf *wolf)
{
	char	*str[4];
	int		i;

	i = 0;
	str[0] = "texture/wall1.xpm";
	str[1] = "texture/wall2.xpm";
	str[2] = "texture/wall3.xpm";
	str[3] = "texture/wall4.xpm";
	while (i < 4)
	{
		wolf->wall[i].mlx_img = mlx_xpm_file_to_image(wolf->mlx, str[i],
				&wolf->wall[i].width, &wolf->wall[i].height);
		if (!wolf->wall[i].mlx_img)
		{
			ft_putstr_fd("Warning: Missing file ", 2);
			ft_putendl_fd(str[i], 2);
		}
		else
			wolf->wall[i].img = (unsigned int *)mlx_get_data_addr(
					wolf->wall[i].mlx_img, &wolf->wall[i].bpp,
					&wolf->wall[i].size_l, &wolf->wall[i].endian);
		++i;
	}
}
