/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 21:54:42 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:23:41 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			len;
	unsigned char	*s_1;
	unsigned char	*s_2;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	len = 0;
	while (len < n && (*(s_1 + len) != '\0' || *(s_2 + len) != '\0'))
	{
		if (*(s_1 + len) == *(s_2 + len))
		{
			len++;
			continue;
		}
		else if (*(s_1 + len) > *(s_2 + len))
			return (*(s_1 + len) + *(s_2 + len));
		else if (*(s_1 + len) < *(s_2 + len))
			return (*(s_1 + len) - *(s_2 + len));
		len++;
	}
	if (n == len)
		return (0);
	else
		return (*(s_1 + len) - *(s_2 + len));
}
