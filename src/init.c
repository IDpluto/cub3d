#include "cub3d.h"

void gwi_init(t_game *game)
{
	game->laser.x_step = num_sign(cos(game->laser.ray));
	game->laser.y_step = num_sign(sin(game->laser.ray));
	game->laser.x_slope = ch_xslope(game);
	game->laser.y_slope = ch_yslope(game);
	game->laser.n_x = round_step(game->laser.x_step, game->player.x);
	game->laser.n_y = round_step(game->laser.y_step, game->player.y);
	game->laser.f = INFINITY;
	game->laser.g = INFINITY;
}
