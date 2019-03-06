/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 16:32:37 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 17:06:58 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				check_size_x(char *str, int *x, int y)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i += ft_intlen(ft_atoi(&str[i]));
			++ret;
		}
		else if (str[i] == ',')
			++i;
		else
			return (3);
	}
	if (y == 0)
		*x = ret;
	else if (ret != *x)
		return (4);
	return (0);
}

int				ft_alloc_map(t_wolf *wolf, char **av, int x, int y)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if ((wolf->error = check_size_x(line, &x, y)))
		{
			free(line);
			return (wolf->error);
		}
		free(line);
		++y;
	}
	close(fd);
	fd = -1;
	if (!(wolf->map = (t_map**)malloc(sizeof(t_map*) * (y))))
		return (2);
	while (++fd < y)
		if (!(wolf->map[fd] = (t_map*)malloc(sizeof(t_map) * (x))))
			return (2);
	wolf->map_width = x;
	wolf->map_height = y;
	return (0);
}

void			ft_fill_map(char *str, t_map *map, int discover)
{
	int		i;
	int		x;
	int		strlen;

	i = 0;
	x = 0;
	strlen = ft_strlen(str);
	while (i < strlen)
	{
		if (ft_isdigit(str[i]))
		{
			map[x].type = (unsigned int)ft_atoi(&str[i]);
			map[x].discover = discover;
			map[x].win = 0;
			i += ft_intlen(ft_atoi(&str[i]));
			++x;
		}
		++i;
	}
}

int				ft_fill_tab(t_wolf *wolf, char **av)
{
	char	*line;
	int		fd;
	int		y;

	if ((fd = open(av[1], O_RDONLY)) < 2)
	{
		ft_putstr_fd("Error: can't open ", 2);
		ft_putendl_fd(av[1], 2);
		return (1);
	}
	if ((wolf->error = ft_alloc_map(wolf, av, 0, 0)))
		return (wolf->error);
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_fill_map(line, wolf->map[y], DISCOVER);
		y++;
		free(line);
	}
	close(fd);
	return (0);
}
