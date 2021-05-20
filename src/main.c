#include "cub3d.h"

/*int main()
{
	t_game *game;
	if (!(game = malloc(sizeof(t_game))))
		return (0);
	if (parsing_cub(&game.map, fd) == -1)
		return (0);
	game->data.mlx = mlx_init();
	game->data.mlx_win = mlx_new_window(game->data.mlx, game->map.resolution[1], game->map.resolution[2], "Hello world!");
	game->data.img = mlx_new_image(game->data.mlx,game->map.resolution[1], game->map.resolution[2]);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length,
								&game->data.endian);
	init(game);
	game->player.x = 12;
	game->player.y = 12;
	game->player.p_sight = 255;
	render(game);
	mlx_hook(game->data.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, game);
	mlx_loop(game->data.mlx);
	return (0);
}
*/

int main (int argc, char *argv[])
{
	t_game *game;
	int fd;


	if (!(game = malloc(sizeof(t_game))))
		return (0);
	fd = open(argv[1], O_RDONLY);
	init_map(game);
	if (parsing_cub(&game->map, fd) == -1)
		return (0);
	if (!(parsing_map(fd, &game->player, &game->map.height, &game->map)))
		return (0);
	init_game(game);
	load_texture(game);
	render(game);
	mlx_hook(game->data.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, game);
	mlx_loop(game->data.mlx);
	return (0);
}
