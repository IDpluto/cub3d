#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../mlx/mlx.h"
#include "../libft/libft.h"

#define	MAP_X					28
#define	MAP_Y					24
#define	EPS						(1e-06)
#define	S_X						1080
#define	S_Y						720
#define	FOV						60
#define	WALL_H					1.0
#define _2PI					6.28318530717958647692
#define  MOVE_UNIT				0.1
#define ROT_UNIT				0.1
#define KEY_RIGHT				124
#define KEY_LEFT				123
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_release	3
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2

typedef enum {DIR_N = 0, DIR_E, DIR_W, DIR_S} e_dirt;

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
	void	*mlx;
	void	*mlx_win;
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
	double fov_h;
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
	double p_nsight;
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
	t_data data;
	t_graphic graphic;
	e_dirt wdir;
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
int map_get_cell(int x, int y);
//e_bool get_wall_intersection(t_laser *t_pos, e_dirt wdir);
double cast_single_ray(t_laser *t_pos);
void gr_yfind(t_laser *laser, t_data *img, int color);
void draw_wall(t_laser *laser, int color);
int get_wall_height(t_laser *laser);
int min(int a, int b);
int max(int a, int b);
int player_move(t_laser *laser, int keycode, double amt);
static int get_move_offset(double th, int keycode, double amt, double *pdx, double *pdy);
int key_direction(int keycode, int key_d);
void player_rotate(t_laser *laser, double th);


enum {VERT, HORIZ};

typedef enum {false = 0, true = 1} e_bool;


#endif
