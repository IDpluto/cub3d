/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:25:27 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 13:25:33 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		ch_xslope(t_game *game)
{
	if (game->laser.x_step == 0)
		return (INFINITY);
	else
		return (tan(game->laser.ray));
}

double		ch_yslope(t_game *game)
{
	if (game->laser.y_step == 0)
		return (INFINITY);
	else
		return (1. / tan(game->laser.ray));
}

int			ch_map(int step, double n)
{
	if (step == 1)
		return ((int)n);
	else
		return ((int)n - 1);
}

double		round_step(int xy_step, double p_xy)
{
	if (xy_step > 0)
		return (floor(p_xy) + 1);
	else if (xy_step < 0)
		return (ceil(p_xy) - 1);
	else
		return (p_xy);
}
