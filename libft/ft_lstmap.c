/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:06:46 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:08:53 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	if (!(tmp = ft_lstnew((*f)(lst->content))))
		return (NULL);
	newlst = tmp;
	lst = lst->next;
	while (lst)
	{
		if (!(tmp = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&newlst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&newlst, tmp);
	}
	return (newlst);
}
