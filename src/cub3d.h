#ifndef CUB3D_H
#define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
#include "../gnl/get_next_line.h"
#include "../mlx/mlx.h"
#include "../libft/libft.h"

# define All_DIRECTIONS "WSEN"
# define ALLOWED_TEXTS "012 WSEN"
#define	EPS						(1e-06)
#define	FOV						60
#define	WALL_H					1.0
#define _2PI					6.28318530717958647692
#define _PI					3.14159265358979323846
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
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define N_ANGLE						0
# define S_ANGLE						180
# define W_ANGLE						270
# define E_ANGLE						90
# define NO 0
# define SO 3
# define WE 1
# define EA 2
# define S 4
# define R 5
# define F 6
# define C 7




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

typedef struct {
    int tex;
    int x, y;
    double dist;
    double th;
} sprite_t;

typedef struct s_texture
{
	int			num;
	int			tex[5][TEX_WIDTH * TEX_WIDTH];
	double 		txratio;
	double		step;
	double		wall_x;
	double		tex_pos;
}				t_texture;

typedef struct s_node
{
	int			y;
	char		*line;
	struct s_node *next;
}				t_node;

typedef struct s_map
{
	char		**map;
	char		**map_visited;
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
	int		check;
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
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			width;
	int			height;
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
	t_texture	tex;
	sprite_t	sprite;
}			t_game;

double		ch_xslope(t_game *game);
double		ch_yslope(t_game *game);
int			ch_map(int step, double n);
void		find_direction(t_game *game);
void		wall_dist(t_game *game);
void		wall_hit_grid(t_game *game);
int			get_wall_height(t_game *game);
void		draw_wall(t_game *game);
void		render(t_game *game);
void gr_yfind(t_game *game, int *tex);
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
double		global_fov_v(t_game *game);
e_bool		get_wall_intersection(t_game *game);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		parsing_cub(t_map *map, int fd);
int put_in_texture(t_map *map, char *line);
char			*put_element(char *str);
char			*clean_string(char *str, int i);
int				save_map_info(char *line);
char			*save_path(char *line);
int				pass_space(char *line);
void	save_res_info(t_map *map, char *line);
int				parsing_map(int fd, t_player *player, int *map_height, t_map *map);
void			find_player(char *line, t_player *player, int num);
void			set_player_dir_info(t_player *player, int dir_x, int dir_y);
void			set_player_pos_info(t_player *player, int pos_x, int pos_y);
void load_texture(t_game *game);
void		make_texture(t_game *game, int i);
int				ft_isspace(char line);
int			error_file(t_map *map);
int		create_trgb(int t, int r, int g, int b);
char			**free_all(char **line);
t_node			*create_node();
t_node			*next_node(t_node *curr);
char			**list_to_array(t_node *list, int size);
void			add_node(t_node *axis, int value);
void		free_node(t_node *node);
void			init_data(t_game *game);
int			error_file(t_map *map);
void get_txratio(t_game *game);
double global_fov_h(t_game *game);
void init_game(t_game *game);
void			init_data(t_game *game);
void			init_mlx(t_game *game);
void init_map(t_game *game);
void gwi_init(t_game *game);
double deg2rad(double d);
int map_get_cell(int x, int y, t_map *map);
double get_fov_min_dist(t_game *game);
void floor_ceil(t_game *game);
#endif
