#include "cub3d.h"

void player_rotate(t_game *game)
{
    game->player.p_sight += game->player.p_nsight;
    if (game->player.p_sight < 0)
        game->player.p_sight += _2PI;
    else if (game->player.p_sight > _2PI)
        game->player.p_sight -= _2PI;
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
