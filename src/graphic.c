#include "cub3d.h"

int get_wall_height(t_game *game)
{
    game->global.fov_v = fov_v(game);
    game->global.fov_h = 2.0 * game->laser.wdist * tan(game->global.fov_v / 2.0);
    return ((int)(S_Y * (WALL_H / game->global.fov_h)));
}

void draw_wall(t_game *game, int color)
{
    game->graphic.wh = get_wall_height(game);
    game->graphic.y0 = (int)((S_Y - game->graphic.wh) / 2.0);
    game->graphic.y1 = game->graphic.y0 + game->graphic.wh - 1;
    game->graphic.y_start = max(0, game->graphic.y0);
    game->graphic.y_end = min(S_Y - 1, game->graphic.y1);
    gr_yfind(game, color);
}

void gr_yfind(t_game *game, int color)
{
	int y;

    y = game->graphic.y_start;
    while (y < game->graphic.y_end)
    {
        my_mlx_pixel_put(game->data.img, game->laser.x, y, color);
        y++;
    }
}
void render(t_game *game)
{
    mlx_clear_window(game->data.mlx, game->data.mlx_win);
    game->laser.x = 0;
    while(game->laser.x < S_X)
    {
        game->laser.wdist = cast_single_ray(game);
        printf("** ray %3d : dist %.2f\n", game->laser.x, game->laser.wdist);
        game->laser.x++;
        draw_wall(game, wall_colors[game->wdir]);
    }
    mlx_put_image_to_window(game->data.mlx, game->data.mlx_win, game->data.img, 0, 0);
    mlx_destroy_image(game->data.mlx, game->data.img);
    game->data.img = mlx_new_image(game->data.mlx, S_X, S_Y);
    game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length,
										&game->data.endian);
}
