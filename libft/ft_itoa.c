/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:38:38 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 16:06:13 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				num(long nb)
{
	int			len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char		*str;
	long long	tmp;
	int			i;

	tmp = n;
	i = num(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	*(str + i--) = '\0';
	if (tmp == 0)
	{
		*(str + 0) = 48;
		return (str);
	}
	if (tmp < 0)
	{
		*(str + 0) = '-';
		tmp = tmp * -1;
	}
	while (tmp > 0)
	{
		*(str + i--) = 48 + (tmp % 10);
		tmp = tmp / 10;
	}
	return (str);
}
