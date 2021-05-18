#include "cub3d.h"

double ch_xslope(t_game *game)
{
	if (game->laser.x_step == 0)
		return (INFINITY);
	else
		return(tan(game->laser.ray));
}

double ch_yslope(t_game *game)
{
	if (game->laser.y_step == 0)
		return (INFINITY);
	else
		return(1./tan(game->laser.ray));
}

int ch_mapx(t_laser *laser)
{
    if (laser->x_step == 1)
        return ((int)laser->n_x);
    else
        return ((int)laser->n_x - 1);
}
int ch_mapy(t_laser *laser)
{
    if (laser->y_step == 1)
        return ((int)laser->n_y);
    else
        return ((int)laser->n_y - 1);
}

void find_direction(t_game *game)
{
	if(game->laser.hit_side == VERT)
	{
		if(game->laser.x_step > 0)
			game->wdir = DIR_W;
		else
			game->wdir = DIR_E;
		game->laser.w_x = game->laser.n_x;
		game->laser.w_y = game->laser.f;
	}
	else
	{ /* HORIZ */
		if(game->laser.y_step > 0)
			game->wdir = DIR_S;
		else
			game->wdir = DIR_N;
	game->laser.w_x = game->laser.g;
	game->laser.w_y = game->laser.n_y;
	}
}

double round_step(int xy_step, double p_xy)
{
    if (xy_step > 0)
        return (floor(p_xy) + 1); //내림
    else if (xy_step < 0)
        return (ceil(p_xy) - 1); //올림
    else
        return (p_xy);
}

void wall_dist(t_game *game)
{
	game->laser.dist_v = l2dist(game->player.x, game->player.y, game->laser.n_x, game->laser.f);
	game->laser.dist_h = l2dist(game->player.x, game->player.y, game->laser.g, game->laser.n_y);
	if (game->laser.dist_v < game->laser.dist_h)
	{
		game->laser.map_x = ch_mapx(game);
		game->laser.map_y = (int)game->laser.f;
		game->laser.hit_side = VERT;
	}
	else
	{
		game->laser.map_x = (int)game->laser.g;
		game->laser.map_y = ch_mapy(game);
		game->laser.hit_side = HORIZ;
	}
}

void wall_hit_grid(t_game *game)
{
	if (game->laser.hit_side == VERT)
		game->laser.n_x += game->laser.x_step;
	else
		game->laser.n_y += game->laser.y_step;
}
