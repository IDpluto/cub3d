/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohlee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:31:52 by dohlee            #+#    #+#             */
/*   Updated: 2020/11/25 15:16:21 by dohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_div_count(char const *s, char c)
{
	int				i;
	int				count;

	count = 0;
	if (*s && *s != c)
		count++;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			count++;
		i++;
	}
	return (count);
}

char				*free_s(char **fre)
{
	size_t			i;

	i = 0;
	while (fre[i])
		free(fre[i++]);
	free(fre);
	return (NULL);
}

static char			*ft_column(char const *s, char c, int i, char **fre)
{
	int				j;
	int				k;
	int				tmp;
	char			*n_str;

	j = i;
	while (s[i] && s[i] != c)
		i++;
	tmp = i - j;
	if (tmp == 0)
		return (NULL);
	if (!(n_str = (char *)malloc(sizeof(char) * (tmp + 1))))
	{
		free_s(fre);
		return (NULL);
	}
	k = 0;
	while (j != i)
	{
		n_str[k] = s[j];
		k++;
		j++;
	}
	n_str[k] = '\0';
	return (n_str);
}

char				**ft_split(char const *s, char c)
{
	char			**arr;
	int				i;
	int				j;
	char			*tmp;

	if (!s)
		return (NULL);
	if (!(arr = (char **)malloc(sizeof(char *) * (ft_div_count(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	if (ft_div_count(s, c))
		while (i < (int)ft_strlen(s))
		{
			tmp = ft_column(s, c, i, arr);
			if (tmp && ft_strlen(tmp))
			{
				arr[j] = tmp;
				i += (ft_strlen(arr[j++]) + 1);
			}
			else
				i++;
		}
	arr[j] = NULL;
	return (arr);
}
