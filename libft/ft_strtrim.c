/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 21:51:46 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 14:42:43 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_indexes(char const *s1,
		char *set, int start, int *end)
{
	int		i;

	i = -1;
	if (set && ft_strlen(set) > 0)
	{
		while (set[++i] != '\0')
		{
			if (s1[start] == set[i] && start <= *end)
			{
				start++;
				i = -1;
			}
		}
		i = -1;
		while (set[++i] != '\0')
		{
			if (s1[*end] == set[i] && *end >= start)
			{
				(*end)--;
				i = -1;
			}
		}
	}
	return (start);
}

char		*ft_strtrim(char const *s1, char *set)
{
	int		start;
	int		end;
	char	*p;

	if (!s1)
		return (NULL);
	if (s1[0] == '\0')
	{
		if (!(p = malloc(sizeof(char))))
			return (NULL);
		p[0] = '\0';
		return (p);
	}
	end = ft_strlen(s1) - 1;
	start = find_indexes(s1, set, 0, &end);
	if (end < start)
	{
		if (!(p = malloc(1)))
			return (NULL);
		*p = '\0';
		return (p);
	}
	if (!(p = ft_substr(s1, start, (end - start) + 1)))
		return (NULL);
	return (p);
}
