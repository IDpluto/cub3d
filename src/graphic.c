#include "cub3d.h"

int get_wall_height(t_game *game)
{
	game->global.fov_v = global_fov_v(game);
	game->graphic.fov_h = 2.0 * game->laser.wdist * tan(game->global.fov_v / 2.0);
	return ((int)(game->map.resolution[1] * (WALL_H / game->graphic.fov_h)));
}

void draw_wall(t_game *game)
{
	game->graphic.wh = get_wall_height(game);
	game->graphic.y0 = (int)((game->map.resolution[1] - game->graphic.wh) / 2.0);
	game->graphic.y1 = game->graphic.y0 + game->graphic.wh - 1;
	game->graphic.y_start = max(0, game->graphic.y0);
	game->graphic.y_end = min(game->map.resolution[1] - 1, game->graphic.y1);
	gr_yfind(game, game->tex.tex[game->wdir]);
}
// ~~~ , int *tex
void gr_yfind(t_game *game, int *tex)
{
	int y;
	int color;
	int tx;
	int ty;
	double lum;

	game->tex.txratio = 0;
	get_txratio(game);
	tx = (int)(game->tex.txratio * game->data.width);
	//printf("TEST======%d\n",game->data.width);
	y = game->graphic.y_start;

	while (y < game->graphic.y_end)
	{
		ty = (int)((double)(y - game->graphic.y0) * game->data.height / game->graphic.wh);
		color = tex[TEX_WIDTH * ty + tx];
		my_mlx_pixel_put(&game->data, game->laser.x, y, color);
		y++;
	}
}

void get_txratio(t_game *game)
{
	if (game->wdir == DIR_W || game->wdir == DIR_E)
		game->tex.txratio = game->laser.w_y - floor(game->laser.w_y);
	else
		game->tex.txratio = game->laser.w_x - floor(game->laser.w_x);
}

void render(t_game *game)
{
	mlx_clear_window(game->data.mlx, game->data.mlx_win);

	game->global.fov_h = global_fov_h(game);
	game->laser.x = 0;
	while(game->laser.x < game->map.resolution[0])
	{
		game->laser.wdist = cast_single_ray(game);
		//printf("** ray %3d : dist %.2f\n", game->laser.x, game->laser.wdist);
		game->laser.x++;
		draw_wall(game);
	}
	mlx_put_image_to_window(game->data.mlx, game->data.mlx_win, game->data.img, 0, 0);
	mlx_destroy_image(game->data.mlx, game->data.img);
	game->data.img = mlx_new_image(game->data.mlx, game->map.resolution[0], game->map.resolution[1]);
	game->data.addr = (int*)mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length,
										&game->data.endian);

}
