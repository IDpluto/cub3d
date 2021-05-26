/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:42:30 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 14:42:09 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite			*get_visible_sprites(t_game *game, int *pcnt)
{
	int				n;
	t_sprite		*sp;

	n = 0;
	game->spu.y = -1;
	sp = NULL;
	while (game->map.map[++game->spu.y])
	{
		game->spu.x = -1;
		while (game->map.map[game->spu.y][++game->spu.x])
		{
			if (map_get_cell(game->spu.x, game->spu.y, &game->map) != 2)
				continue;
			if (n == 0)
				sp = (t_sprite*)malloc(sizeof(t_sprite));
			else
				sp = add_sprites(sp, sizeof(t_sprite), n + 1);
			sprites_in(sp, game, n);
			n++;
		}
	}
	*pcnt = n;
	return (sp);
}

void				sprites_in(t_sprite *sp, t_game *game, int n)
{
	sp[n].tex = (map_get_cell(game->spu.x,
				game->spu.y, &game->map) - CELL_WALL) + 5;
	sp[n].x = game->spu.x;
	sp[n].y = game->spu.y;
	sp[n].th = atan2((game->spu.y + 0.5) - (game->player.y),
			(game->spu.x + 0.5) - (game->player.x));
	if (sp[n].th < 0)
		sp[n].th += _2PI;
	sp[n].dist = l2dist(game->player.x, game->player.y,
				game->spu.x + 0.5, game->spu.y + 0.5)
				* cos(game->player.p_sight - sp[n].th);
}

void				*add_sprites(void *src, int size, int n)
{
	void *new_sprite;

	new_sprite = malloc(size * n);
	ft_memcpy(new_sprite, src, size * (n - 1));
	free(src);
	return (new_sprite);
}

void				draw_sprites(t_game *game, double *zbuff, int *tex)
{
	int				nsp;
	t_sprite		*sp;

	nsp = 0;
	sp = get_visible_sprites(game, &nsp);
	game->spu.i = nsp;
	my_qsort(sp, 0, nsp - 1);
	while (--game->spu.i >= 0)
	{
		game->spu.sh = get_wall_height(game, sp[game->spu.i].dist);
		game->spu.angle = sp[game->spu.i].th - game->player.p_sight;
		if (game->spu.angle > _PI)
			game->spu.angle -= _2PI;
		else if (game->spu.angle < -_PI)
			game->spu.angle += _2PI;
		game->spu.cx = (int)((game->global.fovh_2 - game->spu.angle)
			* game->global.pixel_per_angle);
		game->spu.xmin = max(0, game->spu.cx - game->spu.sh / 2);
		game->spu.xmax = min(game->map.resolution[0],
						game->spu.cx + game->spu.sh / 2);
		put_sprite(sp, game, zbuff, tex);
	}
	if (nsp > 0)
		free(sp);
	free(zbuff);
}

void				put_sprite(t_sprite *sp,
					t_game *game, double *zbuff, int *tex)
{
	int				x;
	int				y;
	unsigned int	color;

	x = game->spu.xmin - 1;
	y = game->spu.xmax;
	while (++x < game->spu.xmax)
	{
		if (sp[game->spu.i].dist > zbuff[x] || sp[game->spu.i].dist < 0.9)
			continue;
		game->spu.txratio = (double)(x - game->spu.cx) / game->spu.sh + 0.5;
		game->spu.tx = (int)(game->spu.txratio * game->tex.width[4]);
		game->spu.y0 = (int)((game->map.resolution[1] - game->spu.sh) / 2.0);
		y = max(0, game->spu.y0) - 1;
		while (++y < min(game->map.resolution[1], game->spu.y0 + game->spu.sh))
		{
			game->spu.ty = (int)((double)(y - game->spu.y0)
			* game->tex.height[4] / game->spu.sh);
			color = tex[game->tex.width[4] * game->spu.ty + game->spu.tx];
			if (color == 0xff000000)
				continue;
			my_mlx_pixel_put(&game->data, x, y, color);
		}
	}
}
