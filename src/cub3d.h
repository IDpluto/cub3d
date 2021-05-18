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
#define SPACES					"\t\r "

typedef enum {DIR_N = 0, DIR_E, DIR_W, DIR_S} e_dirt;
enum {VERT, HORIZ};
typedef enum {false = 0, true = 1} e_bool;

typedef struct s_global
{
	double fov_h;
	double fovh_2;
	double fov_v;
	double angle_per_pixel;
}	t_global;

typedef struct s_map
{
	char		**map;
	char		*clean_str;
	char		*element;
	char		*textures[5];
	int			**map_s;
	int			resolution[2];
	int			floor;
	int			celling;
	int			height;
	int			i;
}				t_map;

typedef struct s_player
{
	double x;
	double y;
	double p_sight;
	double p_nsight;
} t_player;

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
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			img_width;
	int			img_height;
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
	double w_x;
	double w_y;
	double ray;
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
	t_data		data;
	e_dirt		wdir;
	t_laser		laser;
	t_global	global;
	t_graphic	graphic;
	t_player	player;
	t_map		map;
}			t_game;

double		ch_xslope(t_game *game);
double		ch_yslope(t_game *game);
int			ch_map(int step, double n);
int			map_get_cell(int x, int y);
void		find_direction(t_game *game);
void		wall_dist(t_game *game);
void		wall_hit_grid(t_game *game);
int			get_wall_height(t_game *game);
void		draw_wall(t_game *game, int color);
void		render(t_game *game);
void		gr_yfind(t_game *game, int color);
int			is_zero(double d);
int			num_sign(double d);
void		gwi_init(t_game *game);
double		round_step(int xy_step, double p_xy);
double		l2dist(double x0, double y0, double x1, double y1);
double		cast_single_ray(t_game *game);
void		wall_hit_grid(t_game *game);
int			key_press(int keycode, t_game *game);
void		init(t_game *game);
int			player_move(t_game *game, int keycode, double amt);
void		player_rotate(t_game *game);
static int	get_move_offset(double th, int keycode, double amt, double *pdx, double *pdy);
int			key_direction(int keycode, int key);
static int	wall_colors(t_game *game);
int			max(int a, int b);
int			min(int a, int b);
double		fov_v(t_game *game);
e_bool		get_wall_intersection(t_game *game);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
