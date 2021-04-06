/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:58:34 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:00:47 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n_l;

	if (!(n_l = malloc(sizeof(t_list))))
		return (NULL);
	n_l->content = content;
	n_l->next = NULL;
	return (n_l);
}
