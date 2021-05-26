#ifndef CUB3D_H
# define CUB3D_H

#define QWE while(1){}
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "../gnl/get_next_line.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# define ALL_DIRECTIONS "WSEN"
# define ALLOWED_TEXTS "012 WSEN"
# define EPS					0.0000001
# define FOV					45
# define WALL_H					1.0
# define CELL_WALL				1
# define _2PI					6.28318530717958647692
# define _PI					3.14159265358979323846
# define _PI_2					1.57079632679489661923
# define MOVE_UNIT				0.05
# define ROT_UNIT	 			0.03
# define KEY_RIGHT				124
# define KEY_LEFT				123
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_REALESE	3
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define SPACES					"\t\r "
# define N_ANGLE				0
# define S_ANGLE				180
# define W_ANGLE				270
# define E_ANGLE				90
# define NO						0
# define SO						3
# define WE						1
# define EA						2
# define S						4
# define R						5
# define F						6
# define C 						7
# define HX						"2231"
# define HY						"3122"

typedef enum	e_dirt
{
	DIR_N = 0,
	DIR_E,
	DIR_W,
	DIR_S
}				t_dirt;

enum {VERT, HORIZ};

typedef enum	e_bool
{
	false = 0, true = 1
}				t_bool;

typedef struct	s_global
{
	double fov_h;
	double fovh_2;
	double fov_v;
	double angle_per_pixel;
	double pixel_per_angle;
}				t_global;
typedef struct	s_sp_utils
{
	int			x;
	int			y;
	int			i;
	int			j;
	int			xmin;
	int			xmax;
	int			cx;
	double		txratio;
	int			tx;
	int			ty;
	int			color;
	int			y0;
	int			sh;
	double		angle;

}				t_sp_utils;

typedef struct	s_sprite
{
	int			tex;
	int			x;
	int			y;
	double		dist;
	double		th;
}				t_sprite;

typedef struct	s_texture
{
	int			num;
	int			*tex[5];
	double		txratio;
	double		step;
	double		wall_x;
	double		tex_pos;
	int			width[5];
	int			height[5];
}				t_texture;

typedef struct		s_node
{
	int				y;
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct	s_map
{
	char		**map;
	char		**map_visited;
	char		*clean_str;
	char		*element;
	char		*textures[5];
	int			resolution[2];
	int			floor;
	int			celling;
	int			height;
	int			i;
	int			resolution_check;
	int			fc_check;
	int			texture_check;
	int			cx;
	int			cy;
	int			h;
	int			x;
	int			y;
}				t_map;

typedef struct	s_player
{
	int			check;
	double		x;
	double		y;
	double		p_sight;
	double		p_nsight;
	int			num;
}				t_player;

typedef struct	s_graphic
{
	int			wh;
	int			y0;
	int			y1;
	int			y_start;
	int			y_end;
	double		fov_h;
}				t_graphic;

typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			width;
	int			height;
	int			endian;
}				t_data;

typedef struct	s_laser
{
	int		y;
	int		x;
	int		x_step;
	int		y_step;
	int		map_x;
	int		map_y;
	int		hit_side;
	int		cell;
	double	w_x;
	double	w_y;
	double	ray;
	double	wdist;
	double	x_slope;
	double	y_slope;
	double	n_x;
	double	n_y;
	double	f;
	double	g;
	double	dist_v;
	double	dist_h;
}				t_laser;

typedef struct	s_game
{
	t_data		data;
	t_dirt		wdir;
	t_laser		laser;
	t_global	global;
	t_graphic	graphic;
	t_player	player;
	t_map		map;
	t_texture	tex;
	t_sp_utils	spu;
	int			moving_forward;
	int			moving_behind;
	int			moving_right;
	int			moving_left;
	int			turn_right;
	int			turn_left;
	int			keycode;
	int			**visible;
	int			sp_n;
	int			i;
	int			sx;
	int			sy;

}				t_game;

double		ch_xslope(t_game *game);
double		ch_yslope(t_game *game);
int			ch_map(int step, double n);
void		find_direction(t_game *game);
void		wall_dist(t_game *game);
void		wall_hit_grid(t_game *game);
int			get_wall_height(t_game *game, double dist);
void		draw_wall(t_game *game);
void		render(t_game *game);
void		gr_yfind(t_game *game, int *tex);
int			is_zero(double d);
int			num_sign(double d);
void		gwi_init(t_game *game);
double		round_step(int xy_step, double p_xy);
double		l2dist(double x0, double y0, double x1, double y1);
double		cast_single_ray(t_game *game);
void		wall_hit_grid(t_game *game);
int			key_press(int keycode, t_game *game);
void		init(t_game *game);
int			player_move(t_game *game, int keycode);
void		player_rotate(t_game *game);
int			get_move_offset(t_game *game,
			int keycode, double *pdx, double *pdy);
int			key_direction(int keycode, int key);
int			wall_colors(t_game *game);
int			max(int a, int b);
int			min(int a, int b);
double		global_fov_v(t_game *game);
t_bool		get_wall_intersection(t_game *game);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			parsing_cub(t_map *map, int fd);
int			put_in_texture(t_map *map, char *line);
char		*put_element(char *str);
char		*clean_string(char *str, int i);
int			save_map_info(char *line);
char			*save_path(char *line);
int			pass_space(char *line);
void		save_res_info(t_map *map, char *line);
int			parsing_map(int fd, t_player *player,
			int *map_height, t_map *map);
void		find_player(char *line, t_player *player, int num);
void		set_player_dir_info(t_player *player, int dir_x, int dir_y);
void		set_player_pos_info(t_player *player, int pos_x, int pos_y);
void		load_texture(t_game *game);
void		make_texture(t_game *game, int i);
int			ft_isspace(char line);
int			error_file(t_map *map);
int			create_trgb(int t, int r, int g, int b);
char		**free_all(char **line);
t_node		*create_node(void);
t_node		*next_node(t_node *curr);
char		**list_to_array(t_node *list, int size);
void		free_node(t_node *node);
void		init_data(t_game *game);
int			error_file(t_map *map);
void		get_txratio(t_game *game);
void		init_game(t_game *game);
void		init_data(t_game *game);
void		init_mlx(t_game *game);
void		init_map(t_game *game);
void		gwi_init(t_game *game);
double		deg2rad(double d);
int			map_get_cell(int x, int y, t_map *map);
double		get_fov_min_dist(t_game *game);
void		floor_ceil(t_game *game);
void		my_qsort(t_sprite *sp, int start, int end);
void		put_sprite(t_sprite *sp, t_game *game, double *zbuff, int *tex);
void		draw_sprites(t_game *game, double *zbuff, int *tex);
t_sprite	*get_visible_sprites(t_game *game, int *pcnt);
int			getpivot(t_sprite *sp, int start, int end);
int			**visible_malloc(int map_x, int map_y);
int			check_map(t_map *map);
void		error_all(int i);
void		macro_init(t_game *game);
int			key_loop(t_game *game);
int			key_release(int keycode, t_game *game);
void		*add_sprites(void *src, int size, int n);
void		gr_init(t_graphic *graphic);
void		map_direction_setting(t_player *player,
			char *line, double angle, int i);
void		map_to_array(t_map *map, t_node *head, int *map_height);
int			color_setting(int *int_colors, int i, char **colors);
void		sprites_in(t_sprite *sp, t_game *game, int n);
int				error_input(int argc, char *argv[]);
#endif
