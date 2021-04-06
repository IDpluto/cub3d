/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:42:05 by dohlee            #+#    #+#             */
/*   Updated: 2020/10/31 15:50:28 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long long	ans;
	char				sig;

	ans = 0;
	sig = '+';
	while (' ' == *str || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		sig = *str;
		str++;
	}
	while ('0' <= *str && *str <= '9')
		ans = (ans * 10) + (*str++ - '0');
	if (ans > 9223372036854775807)
	{
		return (sig == '-' ? 0 : -1);
	}
	else
		return (sig == '-' ? -ans : ans);
}
