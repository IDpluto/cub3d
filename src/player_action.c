/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:42:08 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 12:42:09 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_rotate(t_game *game)
{
	game->player.p_sight += game->player.p_nsight;
	if (game->player.p_sight < 0)
		game->player.p_sight += _2PI;
	else if (game->player.p_sight > _2PI)
		game->player.p_sight -= _2PI;
}

int		player_move(t_game *game, int keycode)
{
	double d_x;
	double d_y;

	d_x = game->player.x;
	d_y = game->player.y;
	if (get_move_offset(game, keycode, &game->player.x, &game->player.y) < 0)
		return (-1);
	if (map_get_cell((int)game->player.x, (int)game->player.y, &game->map) == 1)
	{
		game->player.x = d_x;
		game->player.y = d_y;
		return (-1);
	}
	return (0);
}

int		get_move_offset(t_game *game, int keycode, double *pdx, double *pdy)
{
	double th;

	keycode = 0;
	th = game->player.p_sight;
	if (game->moving_forward)
	{
		*pdx += 1 * MOVE_UNIT * cos(th);
		*pdy += 1 * MOVE_UNIT * sin(th);
	}
	if (game->moving_behind)
	{
		*pdx += -1 * MOVE_UNIT * cos(th);
		*pdy += -1 * MOVE_UNIT * sin(th);
	}
	if (game->moving_left)
	{
		*pdx += MOVE_UNIT * cos(th + 1 * _PI_2);
		*pdy += MOVE_UNIT * sin(th + 1 * _PI_2);
	}
	if (game->moving_right)
	{
		*pdx += MOVE_UNIT * cos(th + -1 * _PI_2);
		*pdy += MOVE_UNIT * sin(th + -1 * _PI_2);
	}
	return (0);
}
