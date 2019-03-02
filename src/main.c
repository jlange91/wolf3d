/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:23:16 by jlange            #+#    #+#             */
/*   Updated: 2018/04/10 18:48:25 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_wolf(t_wolf *wolf)
{
	search_intersections(wolf);
	display_screen(wolf);
	display_minimap(wolf);
}

int		main(int ac, char **av)
{
	t_wolf wolf;

	wolf.map = NULL;
	if (ft_init(&wolf, ac, av) > 0)
	{
		ft_error(wolf.error);
		ft_free(&wolf);
		return (1);
	}
	else
	{
		ft_wolf(&wolf);
		mlx_loop(wolf.mlx);
		ft_free(&wolf);
	}
	return (0);
}
