/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:31:20 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 12:50:07 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				pass_space(char *line)
{
	int			i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
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

char			*clean_string(char *str, int i)
{
	char		*clean_str;

	clean_str = ft_strtrim(str + i, SPACES);
	free(str);
	return (clean_str);
}
