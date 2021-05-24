#include "cub3d.h"


t_sprite	*get_visible_sprites(t_game *game, int *pcnt)
{
	int n;
	int x;
	int y;
	t_sprite *sp;

	n = 0;
	y = 0;
	sp = NULL;
	while (game->map.map[y])
	{
		x = -1;
		while (game->map.map[y][++x])
		{
			if (map_get_cell(x, y, &game->map) != 2)
				continue;

			if (n == 0)
				sp = (t_sprite*)malloc(sizeof(t_sprite));
			else
				sp = (t_sprite*)realloc(sp, sizeof(t_sprite)*(n + 1));
			sp[n].tex = (map_get_cell(x, y, &game->map) - CELL_WALL) + 5;
			sp[n].x = x;
			sp[n].y = y;
			sp[n].th = atan2((y + 0.5) - (game->player.y),
				(x + 0.5) - (game->player.x));
			if (sp[n].th < 0)
				sp[n].th += _2PI;
			sp[n].dist = l2dist(game->player.x, game->player.y,
				x + 0.5, y + 0.5) * cos(game->player.p_sight - sp[n].th);
			n++;
		}
		y++;
	}

	*pcnt = n;
	game->sp_n = n;
	return (sp);
}


void	draw_sprites(t_game *game, double *zbuff, int *tex)
{
	int nsp;
	int i;
	t_sprite *sp;

	nsp = 0;
	sp = get_visible_sprites(game, &nsp);
	my_qsort(sp, 0, nsp - 1);
	i = game->sp_n - 1;
	while (i >= 0)
	{
		sp->sh = get_wall_height(game, sp[i].dist);
		sp->angle = sp[i].th - game->player.p_sight;
		if (sp->angle > _PI)
			sp->angle -= _2PI;
		else if (sp->angle < -_PI)
			sp->angle += _2PI;
		sp->cx = (int)((game->global.fovh_2 - sp->angle)
			* game->global.pixel_per_angle);
		sp->xmin = max(0, sp->cx - sp->sh / 2);
		sp->xmax = min(game->map.resolution[0], sp->cx + sp->sh / 2);
		game->i = i;
		put_sprite(sp, game, zbuff, tex);
		i--;
	}
	if (nsp > 0)
		free(sp);
}

void	put_sprite(t_sprite *sp, t_game *game, double *zbuff, int *tex)
{
	int x;
	int y;
	int i;
	unsigned int color;

	i = game->i;
	x = sp->xmin - 1;

	y = sp->xmax;
	while (++x < sp->xmax)
	{
		if (sp[i].dist > zbuff[x])
			continue;
		if (sp[i].dist < 0.9)
			continue;
		sp->txratio = (double)(x - sp->cx) / sp->sh + 0.5;
		sp->tx = (int)(sp->txratio * game->tex.width[4]);
		sp->y0 = (int)((game->map.resolution[1] - sp->sh) / 2.0);
		y = max(0, sp->y0) - 1;
		while (++y < min(game->map.resolution[1], sp->y0 + sp->sh))
		{
			sp->ty = (int)((double)(y - sp->y0) * game->tex.height[4] / sp->sh);
			color = tex[game->tex.width[4] * sp->ty + sp->tx];
			if (color == 0xff000000)
				continue;
			my_mlx_pixel_put(&game->data, x, y, color);
		}
	}
}

