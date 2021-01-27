/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:07:55 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 16:05:31 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy(char *dst, const char *src)
{
	int		i;

	if (src[0] == '\0')
	{
		dst[0] = '\0';
		return (dst);
	}
	i = -1;
	while (src[++i] != '\0')
	{
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strdup(const char *s)
{
	char	*p;
	int		len;

	len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (*s == '\0')
		len = 1;
	if (!(p = malloc(sizeof(char) * len + 1)))
		return (NULL);
	return (ft_copy(p, s));
}
