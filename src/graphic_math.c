#include "cub3d.h"

double global_fov_h(t_game *game)
{
	return (deg2rad(FOV));
}


double  global_fov_v(t_game *game)
{
	return (game->global.fov_h * (double)game->map.resolution[1]/(double)game->map.resolution[0]);
}

double deg2rad(double d)
{
	d *= M_PI/180.0;
	return (d);
}

double get_fov_min_dist(t_game *game) /* distance to the floor-FOV intersection point */
{
	double t = -1;
	if(t < 0)
		t = WALL_H / (2.0 * tan(game->global.fov_v / 2.0));
	return (t);
}
