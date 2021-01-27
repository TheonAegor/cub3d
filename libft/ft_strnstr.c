/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:42:34 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 16:40:46 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_start(char *hay, char *need, size_t len)
{
	int			i;

	i = 0;
	while (*hay != '\0' && *need != '\0')
	{
		if (*hay == *need)
		{
			i++;
		}
		if (i == (int)len)
			return (1);
		if (*hay != *need)
			return (0);
		hay++;
		need++;
	}
	return (1);
}

char			*ft_strnstr(const char *haystack,
		const char *needle, size_t len)
{
	size_t		src_len;
	char		*d_hs;
	char		*d_nee;
	int			i;

	d_hs = (char *)haystack;
	d_nee = (char *)needle;
	src_len = ft_strlen(d_nee);
	if (src_len == 0)
		return (d_hs);
	i = 0;
	while (d_hs[i] != '\0' && i <= (int)len - (int)src_len)
	{
		if (d_hs[i] == d_nee[0])
		{
			if (ft_start(d_hs + i, d_nee, len))
				return (d_hs + i);
		}
		i++;
	}
	return (NULL);
}
