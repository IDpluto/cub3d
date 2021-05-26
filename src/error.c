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
			error_all(1);
			return (0);
		}
		i++;
	}
	return (1);
}

int				error_input(int argc, char *argv[])
{
	int			fd;
	char		*str;

	if (!(argc >= 2 && argc <= 3))
	 (error_all(8));
	//if (argc == 3)
	//	*sc = check_sc(argv[2]);
	str = ft_strrchr(argv[1], '.');
	if (ft_strlen(str) != 4)
		(error_all(8));
	if (ft_strncmp(str, ".cub", 4))
		(error_all(8));
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		(error_all(8));
	return (fd);
}

void		error_all(int i)
{
	if (i == 0)
	{
		printf("Resolution_error\n");
		exit(0);
	}
	else if (i == 1)
	{
		printf("element_error\n");
		exit(0);
	}
	else if (i == 2)
	{
		printf("map_error\n");
		exit(0);
	}
	else if (i == 3)
	{
		printf("color_argument_error\n");
		exit(0);
	}
	else if (i == 4)
	{
		printf("texture_argument_error\n");
		exit(0);
	}
	else if (i == 5)
	{
		printf("Invalid argument in floor or celling\n");
		exit(0);
	}
	else if (i == 6)
	{
		printf("ERROR - Lack of argument in floor or celling\n");
		exit(0);
	}
	else if (i == 7)
	{
		printf("player_error\n");
		exit(0);
	}
	else if (i == 8)
	{
		printf("file_input_error\n");
		exit(0);
	}
}
