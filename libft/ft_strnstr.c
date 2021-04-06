/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:20:00 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:22:37 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hyk, const char *nde, size_t len)
{
	size_t i;

	if (*hyk)
		;
	if (*nde == '\0')
		return ((char *)hyk);
	i = ft_strlen(nde);
	while (i <= len)
	{
		if (!ft_strncmp(hyk, nde, i))
			return ((char *)hyk);
		len--;
		hyk++;
	}
	return (NULL);
}
