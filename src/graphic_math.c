#include "cub3d.h"

double fov_v(t_game *game)
{
    return (game->global.fov_h * (double)S_Y/(double)S_X);
}
