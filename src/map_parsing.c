#include "cub3d.h"

int		parsing_cub(t_map *map, int fd)
{
	char	*line;
	int		check;

	check = 0;

	while (get_next_line(fd, &line))
	{
		if (!(check += put_in_texture(map, line)))
			return (0);
		if (check >= 8)
			break ;
		free(line);
	}
	free(line);
	return (error_file(map));
}

int		put_in_texture(t_map *map, char *line)
{
	map->clean_str = ft_strtrim(line, SPACES);
	if (!(map->element = put_element(map->clean_str)))
		error_all(1);
	map->i = ft_strlen(map->element);
	map->clean_str = clean_string(map->clean_str, map->i);
	if (!ft_strncmp(map->element, "R", map->i))
		save_res_info(map, map->clean_str);
	else if (!ft_strncmp(map->element, "F", map->i) && map->floor == 0)
		map->floor = save_map_info(map->clean_str);
	else if (!ft_strncmp(map->element, "C", map->i) && map->celling == 0)
		map->celling = save_map_info(map->clean_str);
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
	char		*temp;

	if (str[0] == '\0')
		error_all(1);
	temp = malloc(3);
	i = 0;
	while (!ft_isspace(str[i]) && str[i])
	{
		temp[i] = str[i];
		i++;
		if (i > 2)
		{
			free(temp);
			error_all(1);
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

	i = 1;
	if (line[0] == '\0')
		error_all(3);
	i = pass_space(line + i);
	colors = ft_split(line + i, ',');
	i = -1;
	while (++i < 3)
		if (!colors[i])
			error_all(3);
	i = 0;
	res = create_trgb(0, ft_atoi(colors[0]),
		ft_atoi(colors[1]), ft_atoi(colors[2]));
	free_all(colors);
	return (res);
}

char			*save_path(char *line)
{
	int			i;
	char		*clean_str;
	char		*res;

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

void			save_res_info(t_map *map, char *line)
{
	int			i;

	i = 0;
	if (line[0] == '\0' || !line[3])
		error_all(0);
	map->resolution[0] = ft_atoi(line);
	map->resolution[1] = ft_atoi(line + 3);
}

int				parsing_map(int fd, t_player *player, int *map_height, t_map *map)
{
	t_node		*node;
	t_node		*head;
	char		*line;
	int x;
	int y;

	x = 0;
	y = 0;
	*map_height = 0;
	head = create_node();
	node = head;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 0)
			continue ;
		node = next_node(node);
		node->y = *map_height;
		node->line = ft_strdup(line);
		find_player(node->line, player, *map_height);
		(*map_height)++;
	}
	if (*map_height == 0)
		return (0);
	map->map = list_to_array(head->next, *map_height);
	map->map_visited = list_to_array(head->next, *map_height);
	free_node(head);
	return (1);
}

void			find_player(char *line, t_player *player, int num)
{
	int			i;

	i = -1;
	while (line[++i])
		if (!ft_strrchr(ALLOWED_TEXTS, line[i]))
			player->check = 999;
		else if (line[i] == 'N')
		{
			player->p_sight = _PI * 3 / 2;
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
		else if (line[i] == 'S')
		{
			player->p_sight = _PI / 2;
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
		else if (line[i] == 'W')
		{
			player->p_sight = _PI;
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
		else if (line[i] == 'E')
		{
			player->p_sight = 0;
			set_player_pos_info(player, num, i);
			player->check++;
			line[i] = '0';
		}
}

void			set_player_pos_info(t_player *player, int pos_y, int pos_x)
{
	player->x = pos_x + 0.5;
	player->y = pos_y + 0.5;
}

int				ft_isspace(char line)
{
	if (('\t' <= line && line <= '\r') || line == ' ')
		return (1);
	return (0);
}


int				map_get_cell(int x, int y, t_map *map)
{
	return (map->map[y][x] - '0');
}

