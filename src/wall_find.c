#include "cub3d.h"


double cast_single_ray(t_game *game)
{
	game->global.angle_per_pixel = game->global.fov_h / (S_X - 1.);
	game->global.fovh_2 = game->global.fov_h / 2.0;
	game->laser.ray = (game->laser.p_sight + game->global.fovh_2) - (game->laser.x * game->global.angle_per_pixel);
	if (get_wall_intersection(game) == false)
		return (INFINITY);
	game->laser.wdist = l2dist(game->laser.p_x, game->laser.p_y, game->laser.w_x, game->laser.w_y);
	game->laser.wdist *= cos(game->laser.p_sight - game->laser.ray);
	return (game->laser.wdist);
}

e_bool get_wall_intersection(t_game *game)
{
	gwi_init(game);
	e_bool hit = false;
	while (!hit)
	{
		if (game->laser.x_step != 0)
			game->laser.f = game->laser.x_slope * (game->laser.n_x - game->laser.p_x) + game->laser.p_y;
		if (game->laser.y_step != 0)
			game->laser.g = game->laser.y_slope * (game->laser.n_y - game->laser.p_y) + game->laser.p_x;
		wall_dist(game);
		game->laser.cell = map_get_cell(game->laser.map_x, game->laser.map_y);
		if(game->laser.cell < 0 )
			break;
		if(game->laser.cell == 1 )
		{
			find_direction(game);
			hit = true;
			printf("hit wall!\n");
			break;
		}
		wall_hit_grid(game);
	}
	return (hit);
}
