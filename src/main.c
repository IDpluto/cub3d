#include "cub3d.h"

static int map[MAP_X][MAP_Y]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,1,1,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int is_zero(double d)
{
	if (fabs(d) < EPS)
		return (0);
	else
		return (d);
}

int num_sign(double d)
{
	if(is_zero(d))
		d = 0;
	else if (d > 0)
		d = 1;
	else
		d = -1;
	return (d);
}

double l2dist(double x0, double y0, double x1, double y1)
{
	double dx;
	double dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return sqrt(dx * dx + dy* dy); //sqrt = √ 계산
} // 두점 간의 '거리' 계산

double ch_xslope(t_laser *laser)
{
	if (laser->x_step == 0)
		return (INFINITY);
	else
		return(tan(laser->ray));
}

double ch_yslope(t_laser *laser)
{
	if (laser->y_step == 0)
		return (INFINITY);
	else
		return(1./tan(laser->ray));
}

double ch_nx(int x_step, double p_x)
{
	if (x_step > 0)
		return (floor(p_x) + 1); //내림
	else if (x_step < 0)
		return (ceil(p_x) - 1); //올림
	else
		return (p_x);
}

double ch_ny(int y_step, double p_y)
{
	if (y_step > 0)
		return (floor(p_y) + 1); //내림
	else if (y_step < 0)
		return (ceil(p_y) - 1); //올림
	else
		return (p_y);
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

int map_get_cell(int x, int y)
{
	if (x >= 0 && x < MAP_X &&
		y >= 0 && y < MAP_Y)
    	return (map[x][y]);
	else
		return (-1);
}

double deg2rad(double d)
{
	d *= M_PI/180.0;
	return (d);
}

double rad2deg(double d)
{
	d *= 180.0/M_PI;
	return (d);
}

e_bool get_wall_intersection(t_laser *laser, e_dirt *wdir)
{
	laser->x_step = num_sign(cos(laser->ray));
	laser->y_step = num_sign(sin(laser->ray));
	laser->x_slope = ch_xslope(laser);
	laser->y_slope = ch_yslope(laser);
	laser->n_x = ch_nx(laser->x_step, laser->p_x);
	laser->n_y = ch_ny(laser->y_step, laser->p_y);
	laser->f = INFINITY;
	laser->g = INFINITY;
	e_bool hit = false;

	printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n",
        rad2deg(laser->ray), laser->x_step, laser->y_step, laser->x_slope, laser->y_slope, laser->n_x, laser->n_y);

	while (!hit)
	{
		if (laser->x_step != 0)
			laser->f = laser->x_slope * (laser->n_x - laser->p_x) + laser->p_y;
		if (laser->y_step != 0)
			laser->g = laser->y_slope * (laser->n_y - laser->p_y) + laser->p_x;
		laser->dist_v = l2dist(laser->p_x, laser->p_y, laser->n_x, laser->f);
		laser->dist_h = l2dist(laser->p_x, laser->p_y, laser->g, laser->n_y);
		if (laser->dist_v < laser->dist_h)
		{
			laser->map_x = ch_mapx(laser);
			laser->map_y = (int)laser->f;
			laser->hit_side = VERT;
			printf(" V(%d, %.2f) ->", laser->map_x, laser->f);
		}
		else
		{
			laser->map_x = (int)laser->g;
			laser->map_y = ch_mapy(laser);
			laser->hit_side = HORIZ;
			printf(" H(%.2f, %d) ->", laser->g, laser->map_y);
		}
		laser->cell = map_get_cell(laser->map_x, laser->map_y);
		if(laser->cell < 0 ) //out of map;
			break;
		if(laser->cell == 1 )
		{   /* hit wall? */
			if(laser->hit_side == VERT)
			{
				if(laser->x_step > 0)
					*wdir = DIR_W;
				else
					*wdir = DIR_E;
				laser->w_x = laser->n_x;
				laser->w_y = laser->f;
			}
			else
			{ /* HORIZ */
				if(laser->y_step > 0)
					*wdir = DIR_S;
				else
					*wdir = DIR_N;
				laser->w_x = laser->g;
				laser->w_y = laser->n_y;
			}
			hit = true;
 			printf("hit wall!\n");
			break;
		}
		if (laser->hit_side == VERT)
			laser->n_x += laser->x_step;
		else
			laser->n_y += laser->y_step;
	}
	return (hit);
}

double cast_single_ray(t_laser *laser)
{
	e_dirt wdir;


	laser->angle_per_pixel = laser->fov_h / (S_X - 1.);
	 //printf("TEST: %lf\n", laser->angle_per_pixel);
	laser->fovh_2 = laser->fov_h / 2.0;
	laser->ray = (laser->p_sight + laser->fovh_2) - (laser->x * laser->angle_per_pixel);
	if (get_wall_intersection(laser, &wdir) == false)
		return (INFINITY);
	laser->wdist = l2dist(laser->p_x, laser->p_y, laser->w_x, laser->w_y);
	laser->wdist *= cos(laser->p_sight - laser->ray);
	laser->wdir = wdir;
	return (laser->wdist);
}

static int wall_colors[] = {    /* DIR_N, E, W, S */
		0x00ccaaaa, 0x00aaccaa, 0x00aaaacc, 0x00bbbbbb
};

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double fov_v(t_laser *laser)
{
	return (laser->fov_h * (double)S_Y/(double)S_X);
}

int get_wall_height(t_laser *laser)
{
	laser->graphic.fov_v = fov_v(laser);
	laser->graphic.fov_h = 2.0 * laser->wdist * tan(laser->graphic.fov_v / 2.0);
	return ((int)(S_Y * (WALL_H / laser->graphic.fov_h)));

}

void gr_yfind(t_laser *laser, t_data *img, int color)
{
	int i;
	i = laser->graphic.y_start;
	while (i < laser->graphic.y_end)
	{
		my_mlx_pixel_put(img, laser->x, i, color);
		i++;
	}
}

int max(int a, int b)
{
	if(a > b)
		return (a);
	else
		return (b);
}
int min(int a, int b)
{
	if(a < b)
		return (a);
	else
		return (b);
}

void draw_wall(t_laser *laser, int color)
{
	laser->graphic.wh = get_wall_height(laser);
	laser->graphic.y0 = (int)((S_Y - laser->graphic.wh) / 2.0);
	laser->graphic.y1 = laser->graphic.y0 + laser->graphic.wh - 1;
	laser->graphic.y_start = max(0, laser->graphic.y0);
	laser->graphic.y_end = min(S_Y - 1, laser->graphic.y1);
	gr_yfind(laser, &laser->data, color);
}

void render(t_laser *laser)
{
	mlx_clear_window(laser->data.mlx, laser->data.mlx_win);
	laser->x = 0;
	while(laser->x < S_X)
	{
		laser->wdist = cast_single_ray(laser);
		printf("** ray %3d : dist %.2f\n", laser->x, laser->wdist);
		laser->x++;
		draw_wall(laser, wall_colors[laser->wdir]);
	}
	mlx_put_image_to_window(laser->data.mlx, laser->data.mlx_win, laser->data.img, 0, 0);
	mlx_destroy_image(laser->data.mlx, laser->data.img);
	laser->data.img = mlx_new_image(laser->data.mlx, S_X, S_Y);
	laser->data.addr = mlx_get_data_addr(laser->data.img, &laser->data.bits_per_pixel, &laser->data.line_length,
								&laser->data.endian);


}

void player_rotate(t_laser *laser, double th)
{
	laser->p_sight += th;
	if (laser->p_sight < 0)
		laser->p_sight += _2PI;
	else if (laser->p_sight > _2PI)
		laser->p_sight -= _2PI;
}

int key_direction(int keycode, int key)
{
	if (keycode == key)
		return (1);
	else
		return (-1);
}

static int get_move_offset(double th, int keycode, double amt, double *pdx, double *pdy)
{
	if (keycode == KEY_W || keycode == KEY_S)
	{
		*pdx = key_direction(keycode, KEY_W) * amt * cos(th);
		*pdy = key_direction(keycode, KEY_W) * amt * sin(th);
	}
	else if (keycode == KEY_A || keycode == KEY_D)
	{
		*pdx = amt * cos(th + key_direction(keycode, KEY_A) * M_PI_2);
		*pdy = amt * sin(th + key_direction(keycode, KEY_A) * M_PI_2);
	}
	else
		return (-1);
	return (0);
}


int player_move(t_laser *laser, int keycode, double amt)
{
	double d_x;
	double d_y;
	double n_x;
	double n_y;

	d_x = 0;
	d_y = 0;
	if (get_move_offset(laser->p_sight, keycode, amt, &d_x, &d_y) < 0 )
	{
		fprintf(stderr,"player_move: invalid key %d\n", keycode);
		return (-1);
	}
	n_x = laser->p_x + d_x;
	n_y = laser->p_y + d_y;
	if (map_get_cell((int)n_x, (int)n_y) == -1)
	{
		printf("** bump !\n");
		return (-1);
	}
	laser->p_x = n_x;
	laser->p_y = n_y;
	return (0);
}

int				key_press(int keycode, t_laser *laser)
{
	e_dirt wdir;
	if (keycode < 0 || keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		if (keycode == KEY_LEFT)
			laser->p_nsight = ROT_UNIT * 1;
		else
			laser->p_nsight = ROT_UNIT * -1;
		player_rotate(laser, laser->p_nsight);

		render(laser);
	}
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		if (player_move(laser, keycode, MOVE_UNIT) == 0)
			 render(laser);
	}
	return (0);
}

int main()
{
	t_laser *laser;


	if (!(laser = malloc(sizeof(t_laser))))
		return (0);
	laser->data.mlx = mlx_init();
	laser->data.mlx_win = mlx_new_window(laser->data.mlx, S_X, S_Y, "Hello world!");
	laser->data.img = mlx_new_image(laser->data.mlx, S_X, S_Y);
	laser->data.addr = mlx_get_data_addr(laser->data.img, &laser->data.bits_per_pixel, &laser->data.line_length,
								&laser->data.endian);
	init(laser);
	laser->p_x = 12;
	laser->p_y = 12;
	laser->p_sight = 255;
	render(laser);
	mlx_hook(laser->data.mlx_win, X_EVENT_KEY_PRESS, 0, key_press, laser);
    mlx_loop(laser->data.mlx);
	return (0);
}
