/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:37:52 by taegor            #+#    #+#             */
/*   Updated: 2021/01/30 16:45:03 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ftstrlen(char *s)
{
	int			len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void			*ftcalloc(size_t nmemb, size_t size)
{
	char		*p;
	size_t		len;
	int			i;

	len = nmemb;
	if (!(p = malloc(nmemb * size)))
		return (NULL);
	i = 0;
	while (len)
	{
		p[i] = '\0';
		len--;
		i++;
	}
	return (p);
}

char			*ftstrdup(const char *s)
{
	char		*p;
	int			len;
	int			i;

	len = ftstrlen((char *)s);
	if (!s)
		return (NULL);
	if (*s == '\0')
		len = 1;
	if (!(p = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char			*ftstrjoin(char *s1, char *s2)
{
	char		*p;
	int			len_s1;
	int			len_s2;
	int			i;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len_s1 = ftstrlen(s1);
	len_s2 = ftstrlen(s2);
	if (!(p = ftcalloc((len_s1 + len_s2 + 1), sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len_s1)
		p[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		p[i + len_s1] = s2[i];
	p[len_s1 + len_s2] = '\0';
	free(s1);
	return (p);
}

char			*ftstrchr(char *s, int c)
{
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	if (ftstrlen(s) == 0)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (NULL);
}
