#include "cub3d.h"

int			error_file(t_map *map)
{
	int		fd;
	int		i;

	i = 0;
	while (i < 5)
	{
		fd = open(map->textures[i], O_RDONLY) ;
		if (fd == -1)
		{
			return (0);
		}
		i++;
	}
return (1);
}
