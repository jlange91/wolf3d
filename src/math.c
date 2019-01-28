/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:42:27 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:52:59 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

static double	to_radian(double degree)
{
	return ((degree) * M_PI / 180.0);
}

double			d_cos(double degree)
{
	return (cos(to_radian(degree)));
}

double			d_sin(double degree)
{
	return (sin(to_radian(degree)));
}

double			d_tan(double degree)
{
	return (tan(to_radian(degree)));
}
