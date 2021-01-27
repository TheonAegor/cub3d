/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 23:40:48 by taegor            #+#    #+#             */
/*   Updated: 2020/11/14 23:41:26 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lsize;
	size_t	dsize;

	lsize = ft_strlen(dst);
	if (size > lsize)
		dsize = lsize + ft_strlen(src);
	else
		dsize = size + ft_strlen(src);
	if (size > lsize)
	{
		dst += lsize;
		size -= lsize;
		while (*src && size-- > 1)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	return (dsize);
}
