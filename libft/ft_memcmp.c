/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:18:16 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:12:08 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			len;
	unsigned char	*s_1;
	unsigned char	*s_2;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	len = 0;
	if (!(s1 || s2))
		return (0);
	if (n == 0)
		return (0);
	while (len + 1 < n)
	{
		if (*(s_1 + len) != *(s_2 + len))
			return (*(s_1 + len) - *(s_2 + len));
		len++;
	}
	return (*(s_1 + len) - *(s_2 + len));
}
