#include "cub3d.h"


void init_game(t_game *game)
{
	init_mlx(game);
	macro_init(game);
	gr_init(&game->graphic);
	game->moving_forward = 0;
	game->moving_behind = 0;
	game->moving_right = 0;
	game->moving_left = 0;
	game->turn_right = 0;
	game->turn_left = 0;
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
	game->map.resolution_check = 0;
	game->map.fc_check = 0;
	game->map.texture_check = 0;
	game->player.check = 0;
	game->map.map = NULL;
	game->map.textures[0] = NULL;
	game->map.textures[1] = NULL;
	game->map.textures[2] = NULL;
	game->map.textures[3] = NULL;
	game->map.textures[4] = NULL;
	game->map.floor = 0;
	game->map.celling = 0;
	game->map.height = 0;
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
	game->global.fov_v = global_fov_v(game);
	game->global.fovh_2 = game->global.fov_h / 2.0;
	game->global.pixel_per_angle =
		(game->map.resolution[0] - 1.) / game->global.fov_h;
	game->global.angle_per_pixel =
	game->global.fov_h / (game->map.resolution[0] - 1);
}

void	gr_init(t_graphic *graphic)
{
	graphic->wh = 0;
	graphic->y0 = 0;
	graphic->y1 = 0;
	graphic->y_start = 0;
	graphic->y_end = 0;
}
