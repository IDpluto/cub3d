#include "cub3d.h"

void player_rotate(t_game *game)
{
	game->player.p_sight += game->player.p_nsight;
	if (game->player.p_sight < 0)
		game->player.p_sight += _2PI;
	else if (game->player.p_sight > _2PI)
		game->player.p_sight -= _2PI;
}

int player_move(t_game *game, int keycode, double amt)
{
	double d_x;
	double d_y;
	double n_x;
	double n_y;

	d_x = 0;
	d_y = 0;
	if (get_move_offset(game->player.p_sight, keycode, amt, &d_x, &d_y) < 0 )
	{
		fprintf(stderr,"player_move: invalid key %d\n", keycode);
		return (-1);
	}
	n_x = game->player.x + d_x;
	n_y = game->player.y + d_y;
	if (map_get_cell((int)n_x, (int)n_y, &game->map) == 1)
    {
        printf("** bump !\n");
        return (-1);
    }
	game->player.x = n_x;
	game->player.y = n_y;
	return (0);
}

static int get_move_offset(double th, int keycode, double amt, double *pdx, double *pdy)
{
	if (keycode == KEY_W || keycode == KEY_S)
	{
		*pdx = key_direction(keycode, KEY_W) * amt * cos(th);
		*pdy = key_direction(keycode, KEY_W) * amt * sin(th);
	}
	else if (keycode == KEY_A || keycode == KEY_D)
	{
		*pdx = amt * cos(th + key_direction(keycode, KEY_A) * M_PI_2);
		*pdy = amt * sin(th + key_direction(keycode, KEY_A) * M_PI_2);
	}
	else
		return (-1);
	return (0);
}
