/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <dohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:41:09 by dohlee            #+#    #+#             */
/*   Updated: 2021/05/26 14:22:04 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_node				*create_node(void)
{
	t_node			*node;

	if (!(node = malloc(sizeof(t_node))))
		return (NULL);
	node->y = 0;
	node->line = NULL;
	node->next = NULL;
	return (node);
}

t_node				*next_node(t_node *curr)
{
	t_node		*next;

	next = create_node();
	curr->next = next;
	return (next);
}

char				**list_to_array(t_node *list, int size)
{
	int				i;
	char			**array;

	if (!(array = malloc(sizeof(char**) * (size + 1))))
		return (NULL);
	i = 0;
	while (list)
	{
		array[i] = ft_strdup(list->line);
		i++;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

void				free_node(t_node *node)
{
	t_node			*next;

	while (node->next)
	{
		next = node->next;
		free(node->line);
		free(node);
		node = next;
	}
	free(node->line);
	free(node);
}
