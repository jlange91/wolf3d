/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:51:53 by jlange            #+#    #+#             */
/*   Updated: 2019/03/02 01:22:47 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_dpoint	endpoint2(double angle, double x1, double y1, double lenght)
{
	t_dpoint	ret;
	double		radians;
	double		x2;
	double		y2;

	radians = (M_PI / 180) * angle;
	x2 = x1 + (lenght * cos(radians));
	y2 = y1 + (lenght * sin(radians));
	ret.x = x2;
	ret.y = y2;
	return (ret);
}

t_point		endpoint(double angle, int x1, int y1, double lenght)
{
	t_point		ret;
	double		radians;
	double		x2;
	double		y2;

	radians = (M_PI / 180) * angle;
	x2 = x1 + (lenght * cos(radians));
	y2 = y1 + (lenght * sin(radians));
	ret.x = round(x2);
	ret.y = round(y2);
	return (ret);
}

int			ft_redcross(t_wolf *wolf)
{
	ft_free(wolf);
	exit(0);
}
