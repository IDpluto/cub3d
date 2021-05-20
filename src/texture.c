#include "cub3d.h"

void load_texture(t_game *game)
{
	int i;

	i = 0;
	while (i < 5)
		make_texture(game, i++);
}

void		make_texture(t_game *game, int i)
{
	int		y;
	int		x;


	game->data.img = mlx_xpm_file_to_image(game->data.mlx, game->map.textures[i], &game->data.width, &game->data.height);
	game->data.addr = (int*)mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);
	mlx_put_image_to_window(game->data.mlx, game->data.mlx_win, game->data.img, 0, 0);
	y = 0;
	while (y < game->data.height)
	{
		x = 0;
		while (x < game->data.width)
		{
			game->tex.tex[i][game->data.width * y + x] = game->data.addr[game->data.width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->data.mlx, game->data.img);
	init_data(game);
}

