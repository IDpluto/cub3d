#include "cub3d.h"

int			is_zero(double d)
{
	if (fabs(d) < EPS)
		return (0);
	else
		return (d);
}

int			num_sign(double d)
{
	if (is_zero(d))
		d = 0;
	else if (d > 0)
		d = 1;
	else
		d = -1;
	return (d);
}

double		l2dist(double x0, double y0, double x1, double y1)
{
	double dx;
	double dy;

	dx = x0 - x1;
	dy = y0 - y1;
	return (sqrt(dx * dx + dy * dy));
}

double		rad2deg(double d)
{
	d *= 180.0 / M_PI;
	return (d);
}
