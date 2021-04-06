/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:19:15 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:19:06 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	while (*(src + len) && len + 1 < size)
	{
		*(dest + len) = *(src + len);
		len++;
	}
	if (size != 0)
		*(dest + len) = '\0';
	while (*(src + len))
		len++;
	return (len);
}
