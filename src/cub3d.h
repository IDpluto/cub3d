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

typedef struct	s_data {
	void		*mlx;
	void		*mlx_win;
	void		*ptx;
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
	int x_step;
	int y_step;
	int map_x;
	int map_y;
	int hit_side;
	int cell;
	double p_x;
	double p_y;
	double w_x;
	double w_y;
	double ray;
	double fov_h;
	double fovh_2;
	double p_sight;
	double p_nsight;
	double angle_per_pixel;
	double wdist;
	double x_slope;
	double y_slope;
	double n_x;
	double n_y;
	double f;
	double g;
	double dist_v;
	double dist_h;
}	t_laser;

typedef struct s_game
{
	t_data data;
	e_dirt wdir;
	t_laser laser;
}			t_game;

double		ch_xslope(t_game *game);
double		ch_yslope(t_game *game);
void		find_direction(t_game *game);
void		wall_dist(t_game *game);
int			is_zero(double d);
int			num_sign(double d);
double		l2dist(double x0, double y0, double x1, double y1);
double		round_step(int xy_step, double p_xy);
double		cast_single_ray(t_game *game);
void		wall_hit_grid(t_game *game);




typedef enum {DIR_N = 0, DIR_E, DIR_W, DIR_S} e_dirt;
enum {VERT, HORIZ};

typedef enum {false = 0, true = 1} e_bool;

#endif
