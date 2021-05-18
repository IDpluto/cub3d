#include "cub3d.h"

int		parsing_cub(t_map *map, int fd)
{
	char	*line;
	int		check;

	check = 0;
	line = 0;
	while (get_next_line(fd, &line))
	{
		check += put_in_texture(map, line);
		if (check >= 8)
			break ;
		free(line);
	}
	free(line);
	return (error_file(map));
}

int put_in_texture(t_map *map, char *line)
{
	map->map->clean_str = ft_strtrim(line, SPACES);
	map->element = put_element(map->clean_str);
	map->i = ft_strlen(map->element);
	map->clean_str = clean_string(map->clean_str, map->i);
	if (!ft_strncmp(map->element, "R", map->i))
		save_res_info(map, map->clean_str);
	else if (!ft_strncmp(map->element, "F", map->i) && map->floor == 0)
		map->floor = save_map_info(map->clean_str);
	else if (!ft_strncmp(map->element, "C",  map->i) && map->celling == 0)
		map->celling = save_map_info(map->clean_str	);
	else if (!ft_strncmp(map->element, "NO", map->i) && !map->textures[NO])
		map->textures[NO] = save_path(map->clean_str);
	else if (!ft_strncmp(map->element, "SO", map->i) && !map->textures[SO])
		map->textures[SO] = save_path(map->clean_str);
	else if (!ft_strncmp(map->element, "WE", map->i) && !map->textures[WE])
		map->textures[WE] = save_path(map->clean_str);
	else if (!ft_strncmp(map->element, "EA", map->i) && !map->textures[EA])
		map->textures[EA] = save_path(map->clean_str);
	else if (!ft_strncmp(map->element, "S", map->i) && !map->textures[S])
		map->textures[S] = save_path(map->clean_str);
	free(map->element);
	free(map->clean_str);
	return (1);
}

char			*put_element(char *str)
{
	int			i;
	char		*res;
	char		*temp;

	temp = malloc(3);
	i = 0;
	while (!ft_isspace(str[i]))
	{
		temp[i] = str[i];
		i++;
		if (i > 3)
		{
			free(temp);
			return (NULL);
		}
	}
	temp[i] = '\0';
	return (temp);
}

char			*clean_string(char *str, int i)
{
	char		*clean_str;

	clean_str = ft_strtrim(str + i, SPACES);
	free(str);
	return (clean_str);
}

int				save_map_info(char *line)
{
	int		i;
	int		res;
	char	**colors;

	i = 0;
	i = pass_space(line + i);
	colors = ft_split(line + i, ',');
	i = 0;
	res = create_trgb(0, ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2]));
	free_all(colors);
	return (res);
}

char			*save_path(char *line)
{
	int		i;
	char	*clean_str;
	char	*res;

	i = 0;
	clean_str = ft_strtrim(line, SPACES);
	i = pass_space(clean_str + i);
	res = ft_strdup(clean_str + i);
	free(clean_str);
	return (res);
}

int				pass_space(char *line)
{
	int			i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int map_get_cell(int x, int y)
{
    if (x >= 0 && x < MAP_X &&
        y >= 0 && y < MAP_Y)
        return (map[x][y]);
    else
        return (-1);
}

void	save_res_info(t_map *map, char *line)
{
	int	i;

	map->resolution[0] = ft_atoi(line);
	while (!ft_isspace(line[i]))
		i++;
	map->resolution[1] = ft_atoi(line + i);
}
