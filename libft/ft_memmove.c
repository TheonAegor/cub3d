/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:02:58 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 15:09:02 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	unsigned char		*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (pdst == NULL && psrc == NULL)
		return (pdst);
	if ((size_t)(pdst - psrc) >= len)
		return (ft_memcpy(pdst, psrc, len));
	pdst += len;
	psrc += len;
	if (pdst >= psrc)
	{
		while (len--)
			*--pdst = *--psrc;
	}
	return ((void *)pdst);
}
