#include "cub3d.h"

int			error_file(t_map *map)
{
	int		fd;
	int		i;

	i = 0;
	while (i < 5)
	{
		fd = open(map->textures[i], O_RDONLY);
		if (fd == -1)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void		error_all(int i)
{
	if (i == 0)
	{
		printf("Resolution_error\n");
		exit(-1);
	}
	else if (i == 1)
	{
		printf("element_error\n");
		exit(-1);
	}
	else if (i == 2)
	{
		printf("map_error\n");
		exit(-1);
	}
	else if (i == 3)
	{
		printf("color_argument_error\n");
		exit(-1);
	}
}
