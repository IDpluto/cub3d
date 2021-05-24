#include "cub3d.h"

int			check_map(t_map *map)
{
	int cx;
	int cy;
	int x;
	int y;
	int h;
	int hy[4] = {0, 0, 1, -1};
	int hx[4] = {1, -1, 0, 0};

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
			if (map->map[y][x] == '0' || map->map[y][x] == ' ')
			{
				h = -1;
				while (++h < 4)
				{
					cy = y + hy[h];
					cx = x + hx[h];
					if (cy < 0 || cy > map->height || cx < 0
						|| cx > (int)(ft_strlen(map->map[y]) - 1))
						error_all(2);
				}
			}
	}
	return (1);
}
