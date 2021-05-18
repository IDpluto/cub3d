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
