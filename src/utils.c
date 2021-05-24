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
		pivot = getPivot(sp, start, end);
		my_qsort(sp, start, pivot - 1);
		my_qsort(sp, pivot + 1, end);
	}
}

int				getPivot(t_sprite *sp, int start, int end)
{
	int i;
	int j;
	t_sprite tmp;
	double pivot;

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
