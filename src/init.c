#include "cub3d.h"


void init_game(t_game *game)
{
	init_mlx(game);
	macro_init(game);
}

void			init_data(t_game *game)
{
	game->data.img = mlx_new_image(game->data.mlx, game->map.resolution[0],game->map.resolution[1]);
	game->data.addr = (int*)mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel ,&game->data.line_length, &game->data.endian);
}

void			init_mlx(t_game *game)
{
	game->data.mlx = mlx_init();
	game->data.mlx_win = mlx_new_window(game->data.mlx, game->map.resolution[0], game->map.resolution[1], "title");
}

void init_map(t_game *game)
{
	game->map.map = NULL;
	game->map.textures[0] = NULL;
	game->map.textures[1] = NULL;
	game->map.textures[2] = NULL;
	game->map.textures[3] = NULL;
	game->map.textures[4] = NULL;
	game->map.floor = 0;
	game->map.celling = 0;
	game->sx = game->map.resolution[0];
	game->sy = game->map.resolution[1];
}

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

void macro_init(t_game *game)
{
	game->global.fov_h = deg2rad(FOV);
	game->global.pixel_per_angle =
		(game->map.resolution[0] - 1.) / game->global.fov_h;
}
