#include "cub3d.h"

int			main(int argc, char *argv[])
{
	t_game	*game;
	int		fd;

	if (!argc)
		error_all(1);
	if (!(game = malloc(sizeof(t_game))))
		return (0);
	fd = open(argv[1], O_RDONLY);
	init_map(game);
	if (parsing_cub(&game->map, fd) == -1)
		return (0);
	if (!(parsing_map(fd, &game->player, &game->map.height, &game->map)))
		return (0);
	if (!(check_map(&game->map)))
		return (0);
	init_game(game);
	load_texture(&game->data);
	render(game);
	mlx_hook(game->data.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, game);
	mlx_loop(game->data.mlx);
	return (0);
}
