/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:05:32 by taegor            #+#    #+#             */
/*   Updated: 2020/11/14 19:53:06 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str_to;
	unsigned char	ci;

	str = (unsigned char *)src;
	str_to = (unsigned char *)dst;
	ci = (unsigned char)c;
	i = -1;
	while (++i < n)
	{
		str_to[i] = str[i];
		if (str[i] == ci)
			return ((void *)&str_to[i + 1]);
	}
	return ((void *)NULL);
}
