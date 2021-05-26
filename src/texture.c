/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:28:10 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 13:56:33 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		load_texture(t_game *game)
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
	t_data	*d;

	d = &game->data;
	d->img = mlx_xpm_file_to_image(d->mlx, game->map.textures[i],
			&d->width, &d->height);
	game->tex.width[i] = d->width;
	game->tex.height[i] = d->height;
	game->tex.tex[i] = malloc((sizeof(int) * (d->width * d->height)));
	d->addr = (int*)mlx_get_data_addr(d->img, &d->bits_per_pixel,
			&d->line_length, &d->endian);
	mlx_put_image_to_window(d->mlx, d->mlx_win, d->img, 0, 0);
	y = -1;
	while (++y < d->height)
	{
		x = -1;
		while (++x < d->width)
			game->tex.tex[i][d->width * y + x] = d->addr[d->width * y + x];
	}
	init_data(game);
}
