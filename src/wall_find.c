#include "cub3d.h"

double cast_single_ray(t_game *game)
{
	game->global.angle_per_pixel = game->global.fov_h / (game->map.resolution[0] - 1.);
	game->global.fovh_2 = game->global.fov_h / 2.0;
	game->laser.ray = (game->player.p_sight + game->global.fovh_2) - (game->laser.x * game->global.angle_per_pixel);
	if (get_wall_intersection(game) == false)
		return (INFINITY);
	game->laser.wdist = l2dist(game->player.x, game->player.y, game->laser.w_x, game->laser.w_y);
	//printf("%f,%f,%f,%f====\n", game->player.x, game->player.y, game->laser.w_x, game->laser.w_y);
	//printf("%f=======\n",game->laser.wdist);
	game->laser.wdist *= cos(game->player.p_sight - game->laser.ray);
	return (game->laser.wdist);
}

e_bool get_wall_intersection(t_game *game)
{
	gwi_init(game);
	e_bool hit = false;
	while (!hit)
	{
		if (game->laser.x_step != 0)
			game->laser.f = game->laser.x_slope * (game->laser.n_x - game->player.x) + game->player.y;
		if (game->laser.y_step != 0)
			game->laser.g = game->laser.y_slope * (game->laser.n_y - game->player.y) + game->player.x;
		wall_dist(game);
		game->laser.cell = map_get_cell(game->laser.map_x, game->laser.map_y, &game->map);

		if(game->laser.cell < 0)
			break;
		if(game->laser.cell == 1)
		{
			find_direction(game);
			hit = true;
			break;
		}
		//printf("TEST:%d %d\n", game->laser.map_x, game->laser.map_y);
		//game->visible[game->laser.map_x][game->laser.map_y] = 1;
		wall_hit_grid(game);
	}
	return (hit);
}
