/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:23:49 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 17:51:26 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_line_count(char const *s, char c)
{
	int i;
	int line_num;

	i = -1;
	line_num = 0;
	while (s[++i] == c && s[i] != '\0')
		;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			line_num++;
		}
		if (s[i] == c && s[i] != '\0')
		{
			while (s[i] == c && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			break ;
	}
	return (line_num);
}

static int		ft_find_end(const char *s, char c, int *start, int i)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	*start = i;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			return (i - 1);
		}
		if (s[i] == c)
		{
			while (s[i] == c)
			{
				i++;
			}
		}
	}
	return (i);
}

static char		**ft_create(char **p, const char *s, char c, int line_num)
{
	int			i;
	int			end;
	int			start;

	i = 0;
	start = 0;
	end = 0;
	while (line_num-- > 0)
	{
		end = ft_find_end(s, c, &start, end);
		p[i] = ft_substr(s, start, end - start + 1);
		i++;
		end++;
	}
	p[i] = NULL;
	return (p);
}

char			**ft_split(char const *s, char c)
{
	char		**p;
	int			line_num;

	if (!s)
		return (NULL);
	line_num = ft_line_count(s, c);
	if (!(p = (char **)ft_calloc(sizeof(char *), line_num + 1)))
	{
		return (NULL);
	}
	ft_create(p, s, c, line_num);
	return (p);
}
