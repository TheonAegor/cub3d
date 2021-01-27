/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:33:49 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 15:09:37 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	unsigned char	ci;

	ps = (unsigned char *)s;
	ci = (unsigned char)c;
	while (n-- > 0)
	{
		if (*ps == ci)
			return ((void *)ps);
		ps++;
	}
	return (NULL);
}
