/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:55:44 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 16:59:37 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_error(int error)
{
	char *str[15];

	str[0] = "";
	str[1] = "";
	str[2] = "Error: Malloc error.\n";
	str[3] = "Error: Parse error.\n";
	str[4] = "Error: Only rectangular map.\n";
	str[5] = "Error: No space for player in map.\n";
	str[6] = "Error: dimensions must be odd.\n";
	str[7] = "Error: dimensions must be minimum 5.\n";
	if (error > 1 && error < 15)
		ft_putstr_fd(str[error], 2);
}
