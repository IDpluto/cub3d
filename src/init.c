#include "cub3d.h"

void init(t_laser *laser)
{
	laser->x = 0;
	laser->y = 0;
	laser->wdist = 0;
	laser->p_x = 0;
	laser->p_y = 0;
	laser->p_sight = 0;
	laser->ray = 0;
	laser->w_x = 0;
	laser->w_y = 0;
	laser->fovh_2 = 0;
	laser->angle_per_pixel = 0;
	laser->graphic.wh = 0;
	laser->graphic.y0 = 0;
	laser->graphic.y1 = 0;
	laser->graphic.y_start = 0;
	laser->graphic.y_end = 0;
	laser->graphic.fov_h = 0;
	laser->graphic.fov_v = 0;
	laser->fov_h = deg2rad(FOV);
}
