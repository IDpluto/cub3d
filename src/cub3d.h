#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"

#define	MAP_X	6
#define	MAP_Y	5
#define	EPS		(0.0001)
#define	S_X		400
#define	S_Y		250
#define	FOV		60
#define	WALL_H	1.0

typedef struct s_graphic
{
	int wh;
	int y0;
	int y1;
	int y_start;
	int y_end;
	double fov_v;
	double fov_h;
}				t_graphic;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_laser
{
	int x;
	int y;
	int fov_h;
	int x_step;
	int y_step;
	int map_x;
	int map_y;
	int hit_side;
	int cell;
	double wdist;
	double p_x;
	double p_y;
	//double p_th;
	double p_sight;
	double ray;
	double w_x;
	double w_y;
	double fovh_2;
	double angle_per_pixel;
	double x_slope;
	double y_slope;
	double n_x;
	double n_y;
	double f;
	double g;
	double dist_v;
	double dist_h;
	t_graphic graphic;
}				t_laser;

int is_zero(double d);
int num_sign(double d);
double l2dist(double x0, double y0, double x1, double y1);
void init(t_laser *pos);
double ch_xslope(t_laser *t_pos);
double ch_yslope(t_laser *t_pos);
double ch_nx(int x_step, double p_x);
double ch_ny(int y_step, double p_y);
int ch_mapx(t_laser *t_pos);
int ch_mapy(t_laser *t_pos);
double deg2rad(double d);
double rad2deg(double d);
int map_get_cell(t_laser *t_pos);
//e_bool get_wall_intersection(t_laser *t_pos, e_dirt wdir);
double cast_single_ray(t_laser *t_pos);
void gr_yfind(t_laser *laser, t_data *img, int color);
void draw_wall(t_laser *laser, t_data *img, int color);
int get_wall_height(t_laser *laser);
int min(int a, int b);
int max(int a, int b);

enum {VERT, HORIZ};

typedef enum {false = 0, true = 1} e_bool;
typedef enum {DIR_N = 0, DIR_E, DIR_W, DIR_S} e_dirt;

#endif
