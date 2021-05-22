#include "cub3d.h"

/*int	cmp_sprites( const void* a, const void* b )
{
	if ((((const t_sprite*)a)->dist > ((const t_sprite*)b)->dist))
		return (-1)
	else
		return (0);
}
*/

t_sprite *get_visible_sprites(t_game *game, int *pcnt)
{
	int n;
	int x;
	int y;

	n = 0;
	x = 0;
	y = 0;
	t_sprite* sp = NULL;

	while (x < game->map.resolution[0])
	{
		while(y < game->map.resolution[1])
		{
			//if(game->visible[x][y] == 0  || map_get_cell(y,x, &game->map) <= CELL_WALL)
				//continue;
			sp = (t_sprite*)malloc(sizeof(t_sprite) * (n + 1));
			sp[n].tex = (sp_map_get_cell(y, x, &game->map) - CELL_WALL) + 5;
			sp[n].x = x;
			sp[n].y = y;
			sp[n].th = atan2((y + 0.5) - (game->player.y), (x + 0.5) - (game->player.x));
			if (sp[n].th < 0)
				sp[n].th += _2PI;
			sp[n].dist = l2dist(game->player.x, game->player.y, x + 0.5, y + 0.5) * cos(game->player.p_sight - sp[n].th);
			n++;
			y++;
		}
		x++;
	}
	*pcnt = n;

	return (sp);
}


void	draw_sprites(t_game *game, double *zbuff, int *tex)
{
	int nsp;

	nsp = 0;
	game->global.pixel_per_angle = (game->map.resolution[0] -1.) / game->global.fov_h;
	t_sprite *sp = get_visible_sprites(game, &nsp);
	my_qsort(sp, nsp, sizeof(t_sprite)/sizeof(int) - 1);
	sp->i = 0;
	while (sp->i < nsp)
	{
		sp->sh = get_wall_height(game, sp[sp->i].dist);
		sp->angle = sp[sp->i].th - game->player.p_sight;
		if (sp->angle > _PI)
			sp->angle -= _2PI;
		else if (sp->angle < - _PI)
			sp->angle += _2PI;
		sp->cx = (int)((game->global.fovh_2 - sp->angle) * game->global.pixel_per_angle);
		sp->xmin = max(0, sp->cx - sp->sh/2);
		sp->xmax = min(game->map.resolution[1], sp->cx + sp->sh/2);
		put_sprite(sp, game, &zbuff[game->map.resolution[0]], tex);
	}
	if(nsp > 0)
		free(sp);
}

void put_sprite(t_sprite *sp, t_game *game, double *zbuff, int *tex)
{
	int x;
	int y;
	int i;
	int color;

	i = sp->i;
	x = sp->xmin;
	y = sp->xmax;
	while (x < sp->xmax)
	{
		if (sp[i].dist > zbuff[game->map.resolution[0]])
			continue;
		if (sp[i].dist < _PI_2)
			continue;
		sp->txratio = (double)(x - sp->cx) / sp->sh + 0.5;
		sp->tx = (int)(sp->txratio * game->data.width);
		sp->y0 = (int)((game->map.resolution[1] - sp->sh)/2.0);

		y = max(0, sp->y0);
		while (y < min(game->map.resolution[1], sp->y0 + sp->sh))
		{
			sp->ty = (int)((double)(y - sp->y0) * game->data.height / sp->sh);
			color = tex[TEX_WIDTH * sp->ty + sp->tx];
			if ((color & 0x00ffffff) == 0)
				continue;
			my_mlx_pixel_put(&game->data, x, y, color);
			y++;
		}
		x++;
	}
}

