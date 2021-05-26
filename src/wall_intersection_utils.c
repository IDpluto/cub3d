/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_intersection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:25:11 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 13:25:12 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		find_direction(t_game *game)
{
	if (game->laser.hit_side == VERT)
	{
		if (game->laser.x_step > 0)
			game->wdir = DIR_W;
		else
			game->wdir = DIR_E;
		game->laser.w_x = game->laser.n_x;
		game->laser.w_y = game->laser.f;
	}
	else
	{
		if (game->laser.y_step > 0)
			game->wdir = DIR_S;
		else
			game->wdir = DIR_N;
		game->laser.w_x = game->laser.g;
		game->laser.w_y = game->laser.n_y;
	}
}

void		wall_dist(t_game *game)
{
	game->laser.dist_v = l2dist(game->player.x, game->player.y,
		game->laser.n_x, game->laser.f);
	game->laser.dist_h = l2dist(game->player.x, game->player.y,
		game->laser.g, game->laser.n_y);
	if (game->laser.dist_v < game->laser.dist_h)
	{
		game->laser.map_x = ch_map(game->laser.x_step, game->laser.n_x);
		game->laser.map_y = (int)game->laser.f;
		game->laser.hit_side = VERT;
	}
	else
	{
		game->laser.map_x = (int)game->laser.g;
		game->laser.map_y = ch_map(game->laser.y_step, game->laser.n_y);
		game->laser.hit_side = HORIZ;
	}
}

void		wall_hit_grid(t_game *game)
{
	if (game->laser.hit_side == VERT)
		game->laser.n_x += game->laser.x_step;
	else
		game->laser.n_y += game->laser.y_step;
}
