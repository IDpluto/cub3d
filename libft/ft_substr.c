/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:46:16 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:23:08 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*dst;

	s_len = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	while (*(s + (i + start)) && i < len)
		i++;
	if (!(dst = ft_calloc(sizeof(char), i + 1)))
		return (NULL);
	i = 0;
	while (*(s + (i + start)) && i < len)
	{
		*(dst + i) = *(s + (i + start));
		i++;
	}
	if (s_len <= start)
	{
		dst[0] = 0;
		return (dst);
	}
	return (dst);
}
