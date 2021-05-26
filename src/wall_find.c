/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:21:34 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 13:21:35 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double			cast_single_ray(t_game *g)
{
	g->laser.ray = (g->player.p_sight + g->global.fovh_2)
				- (g->laser.x * g->global.angle_per_pixel);
	if (get_wall_intersection(g) == false)
		return (INFINITY);
	g->laser.wdist = l2dist(g->player.x, g->player.y,
					g->laser.w_x, g->laser.w_y);
	g->laser.wdist *= cos(g->laser.ray - g->player.p_sight);
	return (g->laser.wdist);
}

t_bool			get_wall_intersection(t_game *g)
{
	t_bool hit;

	hit = false;
	gwi_init(g);
	while (!hit)
	{
		if (g->laser.x_step != 0)
			g->laser.f = g->laser.x_slope
			* (g->laser.n_x - g->player.x) + g->player.y;
		if (g->laser.y_step != 0)
			g->laser.g = g->laser.y_slope
			* (g->laser.n_y - g->player.y) + g->player.x;
		wall_dist(g);
		g->laser.cell = map_get_cell(g->laser.map_x, g->laser.map_y, &g->map);
		if (g->laser.cell < 0)
			break ;
		if (g->laser.cell == 1)
		{
			find_direction(g);
			hit = true;
			break ;
		}
		wall_hit_grid(g);
	}
	return (hit);
}
