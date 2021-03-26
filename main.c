#include "cub3d.h"

int is_zero(double d)
{
	if (fabs(d) < EPS)
		return (0);
	else
		return (d);
}

int num_sign(double d)
{
	if(!is_zero(d))
		d = 0;
	else if (d > 0)
		d = 1;
	else
		d = -1;
	return (d);
}

double l2dist(double x0, double y0, double x1, double y1)
{
	double dx = x0 - x1;
	double dy = y0 - y1;
	return sqrt(dx*dx + dy* fdy); //sqrt = √ 계산
} // 두점 간의 '거리' 계산

double ch_xslope(int x_step)
{
	if (x_setp == 0)
		return (INFINITY);
	else
		return(tan(ray));
}

double ch_yslope(int y_step)
{
	if (y_setp == 0)
		return (INFINITY);
	else
		return(1./tan(ray));
}

double ch_nx(int x_step, double p_x)
{
	if (x_step == 0)
		return (floor(p_x) + 1); //내림
	else if (x_step < 0)
		return (ceil(p_x) - 1); //올림
	else
		return (p_x);
}

double ch_ny(int y_step, double p_y)
{
	if (y_step == 0)
		return (floor(p_y) + 1); //내림
	else if (y_step < 0)
		return (ceil(p_y) - 1); //올림
	else
		return (p_y);
}

e_bool get_wall_intersection(double ray, double p_x, double p_y, dir_t* wdir, double* w_x, double* w_y)
{
	int	x_step;
	int	y_step;
	int hit_side;
	int map_x;
	int map_y;
	double x_slope;
	double y_slope;
	double n_x;
	double n_y;
	double f;
	double g;
	double dist_v;
	double dist_h;

	x_step = num_sign(cos(ray));
	y_step = num_sign(sin(ray));
	x_slope = ch_xslope(x_setp);
	y_slope = ch_yslope(y_setp);
	n_x = ch_nx(x_setp, p_x);
	n_y = ch_ny(y_setp, p_y);
	f = INFINITY;
	g = INFINITY;
	e_bool hit = false;

	while (!hit)
	{
		if (x_step != 0)
			f = xslope * (nx-px) + py;
		if (ystep != 0)
			g = yslope * (ny-py) + px;
		dist_v = l2dist(p_x, p_y, n_x, f);
		dist_g = l2dist(p_x, p_y, g, n_y);
	}


}














double cast_single_ray(int x, double p_x, double p_y, double p_th)
{
	double ray;
	double wx;
	double xy;
	double wdist
	e_dir_t wdir;
	static const double FOVH_2;
	static const double ANGLE_PER_PIXEL;

 	ANGLE_PER_PIXEL = FOV_H / (SX-1.);
	FOVH_2 = FOV_H / 2.0;
	ray = (p_th + FOVH_2) - (x * ANGLE_PER_PIXEL);

	if (get_wall_intersection(ray, p_x,p_y, &wdir, &wx, &wy) == false)
		return (INFINITY);
	wdist = l2dist(px, py, wx, wy);
	return (wdist);
}


int main()
{
	double p_x;
	double p_y;
	double p_th;
	double wdist;
	int x;
	int y;

	p_x = 5;
	p_y = 5;
	p_th = 8;
	x = 0;

	while(x < S_X)
	{
		wdist = cast_single_ray(x, p_x, p_y, p_th);
		printf("** ray %3d : dist %.2f\n", x, wdist);
		x++;
	}
	return 0;
}
