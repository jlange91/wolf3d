/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:23:16 by jlange            #+#    #+#             */
/*   Updated: 2019/03/05 14:47:47 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

int		ft_wolf(t_wolf *wolf)
{
	if (wolf->map[(int)wolf->posy][(int)wolf->posx].win == 1)
	{
		ft_putendl("Bravo l'artiste.");
		ft_free(wolf);
		exit(0);
	}
	ft_display_hook(wolf);
	search_intersections(wolf);
	display_screen(wolf);
	display_minimap(wolf);
	return (0);
}

void	init_hook(t_wolf *wolf)
{
	mlx_hook(wolf->screen.win, 2, (1L << 0), key_press_hook, wolf);
	mlx_hook(wolf->screen.win, 3, (1L << 1), key_release_hook, wolf);
	mlx_hook(wolf->screen.win, 17, (1L << 17), ft_redcross, wolf);
	mlx_loop_hook(wolf->mlx, ft_wolf, wolf);
	mlx_loop(wolf->mlx);
}

int		main(int ac, char **av)
{
	t_wolf wolf;

	if (ft_init(&wolf, ac, av) > 0)
	{
		ft_error(wolf.error);
		ft_free(&wolf);
		return (1);
	}
	else
	{
		ft_wolf(&wolf);
		init_hook(&wolf);
		ft_free(&wolf);
	}
	return (0);
}
