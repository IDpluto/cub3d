/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:02:50 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 14:15:10 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				parsing_cub(t_map *map, int fd)
{
	char	*line;
	int		check;

	check = 0;
	line = 0;
	while (get_next_line(fd, &line))
	{
		if (!line[0])
			continue;
		check += put_in_texture(map, line);
		if (check >= 8)
			break ;
		free(line);
	}
	free(line);
	return (error_file(map));
}

int				put_in_texture(t_map *map, char *line)
{
	map->clean_str = ft_strtrim(line, SPACES);
	map->element = put_element(map->clean_str);
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
	else
		error_all(1);
	free(map->element);
	free(map->clean_str);
	return (1);
}

void			find_player(char *line, t_player *player, int num)
{
	int			i;

	player->num = num;
	i = -1;
	while (line[++i])
	{
		if (!ft_strrchr(ALLOWED_TEXTS, line[i]))
			player->check = 999;
		else if (line[i] == 'N')
			map_direction_setting(player, line, _PI / _PI * 3 / 2, i);
		else if (line[i] == 'S')
			map_direction_setting(player, line, _PI / 2, i);
		else if (line[i] == 'W')
			map_direction_setting(player, line, _PI, i);
		else if (line[i] == 'E')
			map_direction_setting(player, line, 0, i);
	}
}

void			map_direction_setting(t_player *player,
				char *line, double angle, int i)
{
	player->p_sight = angle;
	set_player_pos_info(player, player->num, i);
	player->check++;
	line[i] = '0';
}

void			set_player_pos_info(t_player *player, int pos_y, int pos_x)
{
	player->x = pos_x + 0.5;
	player->y = pos_y + 0.5;
}
