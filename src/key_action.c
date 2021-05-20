#include "cub3d.h"

int			 key_press(int keycode, t_game *game)
{
	e_dirt wdir;
	if (keycode < 0 || keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_LEFT)
			game->player.p_nsight = ROT_UNIT * 1;
		else
			game->player.p_nsight = ROT_UNIT * -1;
		player_rotate(game);
		render(game);
	}
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		if (player_move(game, keycode, MOVE_UNIT) == 0)
			 render(game);
	}
	printf("TEST:%f\n",game->player.p_sight);
	return (0);
}

int key_direction(int keycode, int key)
{
	if (keycode == key)
		return (1);
	else
		return (-1);
}
