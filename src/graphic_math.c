/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:07:04 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 11:09:10 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		global_fov_v(t_game *game)
{
	return (game->global.fov_h
	* (double)game->map.resolution[1] / (double)game->map.resolution[0]);
}

double		deg2rad(double d)
{
	d *= M_PI / 180.0;
	return (d);
}

double		get_fov_min_dist(t_game *game)
{
	static double	t;

	t = -1;
	if (t < 0)
		t = WALL_H / (2.0 * tan(game->global.fov_v / 2.0));
	return (t);
}

int			get_wall_height(t_game *g, double dist)
{
	g->graphic.fov_h = 2.0 * dist * tan(g->global.fov_v / 2.0);
	return ((int)(g->map.resolution[1] * (WALL_H / g->graphic.fov_h)));
}

