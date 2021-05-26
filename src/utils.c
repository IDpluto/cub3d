/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:20:52 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 13:21:17 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			**free_all(char **line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
	return (NULL);
}

void			my_qsort(t_sprite *sp, int start, int end)
{
	double pivot;

	if (start < end)
	{
		pivot = getpivot(sp, start, end);
		my_qsort(sp, start, pivot - 1);
		my_qsort(sp, pivot + 1, end);
	}
}

int				getpivot(t_sprite *sp, int start, int end)
{
	int			i;
	int			j;
	t_sprite	tmp;
	double		pivot;

	pivot = sp[end].dist;
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (sp[j].dist <= pivot)
		{
			tmp = sp[++i];
			sp[i] = sp[j];
			sp[j] = tmp;
		}
		j++;
	}
	tmp = sp[i + 1];
	sp[i + 1] = sp[end];
	sp[end] = tmp;
	return (i + 1);
}
