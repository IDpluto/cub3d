#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAP_X  6
#define MAP_Y  5
#define EPS (1e-06)
#define S_X 3
#define FOV 10

int is_zero(double d);
int ft_sign(double d);
double l2dist(double x0, double y0, double x1, double y1);

enum {VERT, HORIZ};

typedef enum {false = 0, true = 1} e_bool;
typedef enum {DIR_N = 0, DIR_E, DIR_W, DIR_S} e_dir_t;
#endif
