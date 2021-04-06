/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:19:07 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:18:42 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	int		i;
	int		count;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (size < dest_len)
		return (size + src_len);
	i = 0;
	count = (int)(size - dest_len - 1);
	while (i < count && *(src + i))
	{
		dest[dest_len] = src[i];
		i++;
		dest_len++;
	}
	*(dest + dest_len) = '\0';
	return (dest_len - i + src_len);
}
