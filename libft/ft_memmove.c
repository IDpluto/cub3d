/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:18:42 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:20:48 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t count)
{
	char		*tmp;
	const char	*s;

	if (!(dest || src))
		return (NULL);
	if (dest <= src)
	{
		tmp = dest;
		s = src;
		while (count--)
			*tmp++ = *s++;
	}
	else
	{
		tmp = dest;
		tmp += count;
		s = src;
		s += count;
		while (count--)
			*--tmp = *--s;
	}
	return (dest);
}
