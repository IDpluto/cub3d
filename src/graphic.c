#include "cub3d.h"

int			get_wall_height(t_game *g, double dist)
{
	g->global.fov_v = global_fov_v(g);
	g->graphic.fov_h = 2.0 * dist * tan(g->global.fov_v / 2.0);
	return ((int)(g->map.resolution[1] * (WALL_H / g->graphic.fov_h)));
}

void		draw_wall(t_game *g)
{
	g->graphic.wh = get_wall_height(g, g->laser.wdist);
	g->graphic.y0 = (int)((g->map.resolution[1] - g->graphic.wh) / 2.0);
	g->graphic.y1 = g->graphic.y0 + g->graphic.wh - 1;
	g->graphic.y_start = max(0, g->graphic.y0);
	g->graphic.y_end = min(g->map.resolution[1] - 1, g->graphic.y1);
	gr_yfind(g, g->tex.tex[g->wdir]);
	floor_ceil(g);
}

void		gr_yfind(t_game *g, int *tex)
{
	int		y;
	int		color;
	int		tx;
	int		ty;

	g->tex.txratio = 0;
	get_txratio(g);
	tx = (int)(g->tex.txratio * g->tex.width[g->wdir]);
	y = g->graphic.y_start;
	while (y < g->graphic.y_end)
	{
		ty = (int)((double)(y - g->graphic.y0)
			* g->tex.height[g->wdir] / g->graphic.wh);
		color = tex[g->tex.width[g->wdir] * ty + tx];
		my_mlx_pixel_put(&g->data, g->laser.x, y, color);
		y++;
	}
}

void		floor_ceil(t_game *g)
{
	int		y;
	double	h;
	double	d;
	double	ec;

	if (g->graphic.y1 < g->map.resolution[1] - 1)
	{
		ec = get_fov_min_dist(g);
		y = g->graphic.y1 + 1;
		while (y < g->map.resolution[1])
		{
			h = (double)(g->map.resolution[1] - 1 - y) / g->map.resolution[1];
			d = ec / (1. - 2 * h);
			my_mlx_pixel_put(&g->data, g->laser.x, y, g->map.floor);
			my_mlx_pixel_put(&g->data, g->laser.x,
							(g->map.resolution[1] - 1 - y), g->map.celling);
			y++;
		}
	}
}

void		get_txratio(t_game *g)
{
	if (g->wdir == DIR_W || g->wdir == DIR_E)
		g->tex.txratio = g->laser.w_y - floor(g->laser.w_y);
	else
		g->tex.txratio = g->laser.w_x - floor(g->laser.w_x);
}

void		render(t_game *g)
{
	double *zbuff;

	mlx_clear_window(g->data.mlx, g->data.mlx_win);
	g->laser.x = 0;
	if (!(zbuff = malloc(sizeof(double) * (g->map.resolution[0] + 1))))
		return ;
	while (g->laser.x < g->map.resolution[0])
	{
		g->laser.wdist = cast_single_ray(g);
		zbuff[g->laser.x] = g->laser.wdist;
		draw_wall(g);
		g->laser.x++;
	}
	draw_sprites(g, zbuff, g->tex.tex[S]);
	mlx_put_image_to_window(g->data.mlx, g->data.mlx_win, g->data.img, 0, 0);
	mlx_destroy_image(g->data.mlx, g->data.img);
	g->data.img = mlx_new_image(g->data.mlx, g->map.resolution[0], g->map.resolution[1]);
	g->data.addr = (int*)mlx_get_data_addr(g->data.img, &g->data.bits_per_pixel,
					&g->data.line_length, &g->data.endian);
}
