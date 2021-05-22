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

void			my_qsort(int data[], int start, int end)
{
	int pivot;

	pivot = getPivot(data, start, end);

	if(start < end)
	{
		pivot = getPivot(data, start, end);
		my_qsort(data, start, pivot - 1);
		my_qsort(data, pivot + 1, end);
	}
}

int getPivot(int data[], int start, int end)
{
	int i;
	int j;
	int tmp;
	int pivot;

	pivot = data[end];
	i = start - 1;
	j = start;

	while (j < end)
	{
		if (data[j] <= pivot)
		{
			tmp = data[++i];
			data[i] = data[j];
			data[j] = tmp;
		}
	}
	tmp = data[i + 1];
	data[i + 1] = data[end];
	data[end] = tmp;
	return (i + 1);
}
