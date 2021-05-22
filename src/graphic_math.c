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
