/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:29:41 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 12:29:41 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int				save_map_info(char *line)
{
	int			i;
	int			res;
	int			j;
	int			int_colors[3];
	char		**colors;

	if (line[0] == '\0')
		error_all(3);
	colors = ft_split(line, ',');
	i = -1;
	while (colors[++i])
	{
		j = -1;
		while (colors[i][++j])
			if (!ft_isdigit(colors[i][j]))
				error_all(5);
	}
	if (i != 3)
		error_all(6);
	i = -1;
	while (++i < 3)
		int_colors[i] = color_setting(int_colors, i, colors);
	res = create_trgb(0, int_colors[0], int_colors[1], int_colors[2]);
	free_all(colors);
	return (res);
}

int				color_setting(int *int_colors, int i, char **colors)
{
	int_colors[i] = ft_atoi(colors[i]);
	if (!(0 <= int_colors[i] && int_colors[i] <= 255))
		error_all(3);
	return (int_colors[i]);
}

char			*save_path(char *line)
{
	int			i;
	char		*clean_str;
	char		*res;

	i = 0;
	clean_str = ft_strtrim(line, SPACES);
	i = pass_space(clean_str + i);
	if (ft_strrchr(clean_str + i, ' '))
		error_all(4);
	res = ft_strdup(clean_str + i);
	free(clean_str);
	return (res);
}

void			save_res_info(t_map *map, char *line)
{
	int		i;
	char	**str;

	if (map->resolution_check == 1)
		error_all(1);
	map->resolution_check = 1;
	if (line[0] == '\0')
		error_all(0);
	str = ft_split(line, ' ');
	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			error_all(0);
	i = 0;
	while (str[i])
		i++;
	if (i != 2)
		error_all(0);
	map->resolution[0] = ft_atoi(str[0]);
	map->resolution[1] = ft_atoi(str[1]);
	free_all(str);
}
