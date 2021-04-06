/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:18:09 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:09:10 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*tmp;
	const char	*s;

	if (!(dest || src))
		return (NULL);
	tmp = dest;
	s = src;
	while (n)
	{
		*tmp++ = *s++;
		n--;
	}
	return (dest);
}
