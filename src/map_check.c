/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:29:31 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 14:19:58 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				parsing_map(int fd, t_player *player,
				int *map_height, t_map *map)
{
	t_node		*node;
	t_node		*head;
	char		*line;

	head = create_node();
	node = head;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 0 && *map_height == 0)
		{
			free(line);
			continue ;
		}
		if (line[0] == 0 && *map_height > 0)
			error_all(2);
		node = next_node(node);
		node->line = ft_strdup(line);
		find_player(node->line, player, *map_height);
		(*map_height)++;
		free(line);
	}
	free(line);
	map_to_array(map, head, map_height);
	return (1);
}

void			map_to_array(t_map *map, t_node *head, int *map_height)
{
	if (*map_height == 0)
		error_all(2);
	map->map = list_to_array(head->next, *map_height);
	map->map_visited = list_to_array(head->next, *map_height);
	free_node(head);
}

int				check_map(t_map *map)
{
	map->y = -1;
	while (map->map[++map->y])
	{
		map->x = -1;
		while (map->map[map->y][++map->x])
			if (map->map[map->y][map->x] == '0'
			|| map->map[map->y][map->x] == '2')
			{
				map->h = -1;
				while (++map->h < 4)
				{
					map->cy = map->y + HY[map->h] - '0' - 2;
					map->cx = map->x + HX[map->h] - '0' - 2;
					if (map->cy < 0 || map->cy > map->height - 1 || map->cx < 0
						|| map->cx > (int)(ft_strlen(map->map[map->cy]) - 1)
						|| !('0' <= map->map[map->cy][map->cx]
						&& map->map[map->cy][map->cx] <= '2'))
						error_all(2);
				}
			}
	}
	return (1);
}
