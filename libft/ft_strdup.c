/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 21:11:18 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:20:59 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *ptr;
	char *tmp;

	if (!(ptr = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (0);
	tmp = ptr;
	while (*s1)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (ptr);
}
