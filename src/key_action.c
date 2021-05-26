/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:11:21 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 11:11:22 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_loop(t_game *game)
{
	if (game->turn_right || game->turn_left)
	{
		if (game->turn_left)
			game->player.p_nsight = ROT_UNIT * 1;
		else if (game->turn_right)
			game->player.p_nsight = ROT_UNIT * -1;
		player_rotate(game);
		render(game);
	}
	if (game->moving_forward || game->moving_behind
			|| game->moving_right || game->moving_left)
	{
		if (player_move(game, game->keycode) == 0)
			render(game);
	}
	return (0);
}

int			key_press(int keycode, t_game *game)
{
	if (keycode < 0 || keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
		game->moving_forward = 1;
	if (keycode == KEY_S)
		game->moving_behind = 1;
	if (keycode == KEY_D)
		game->moving_right = 1;
	if (keycode == KEY_A)
		game->moving_left = 1;
	if (keycode == KEY_RIGHT)
		game->turn_right = 1;
	if (keycode == KEY_LEFT)
		game->turn_left = 1;
	return (0);
}

int			key_release(int keycode, t_game *game)
{
	game->keycode = keycode;
	if (keycode == KEY_W)
		game->moving_forward = 0;
	if (keycode == KEY_S)
		game->moving_behind = 0;
	if (keycode == KEY_D)
		game->moving_right = 0;
	if (keycode == KEY_A)
		game->moving_left = 0;
	if (keycode == KEY_RIGHT)
		game->turn_right = 0;
	if (keycode == KEY_LEFT)
		game->turn_left = 0;
	return (0);
}

int			key_direction(int keycode, int key)
{
	if (keycode == key)
		return (1);
	else
		return (-1);
}
