/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:12:33 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 14:23:33 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			main(int argc, char *argv[])
{
	t_game	*game;
	int		fd;


	if ((fd = error_input(argc, argv) == -1))
		error_all(2);
	if (!(game = malloc(sizeof(t_game))))
		return (0);
	fd = open(argv[1], O_RDONLY);
	init_map(game);
	if (parsing_cub(&game->map, fd) == -1)
		error_all(1);
	if (!(parsing_map(fd, &game->player, &game->map.height, &game->map)))
		error_all(7);
	if (!(check_map(&game->map)))
		return (0);
	if (game->player.check != 1)
		error_all(7);
	init_game(game);
	load_texture(game);
	render(game);
	mlx_hook(game->data.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, game);
	mlx_hook(game->data.mlx_win, X_EVENT_KEY_REALESE, 0, key_release, game);
	mlx_loop_hook(game->data.mlx, key_loop, game);
	mlx_loop(game->data.mlx);
	return (0);
}
