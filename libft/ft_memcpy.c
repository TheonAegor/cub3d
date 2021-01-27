/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:58:07 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 15:08:36 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *restrict_dst, const void *restrict_src,
		size_t n)
{
	size_t		i;
	char		*p_dest;
	const char	*p_src;

	p_dest = restrict_dst;
	p_src = restrict_src;
	i = 0;
	if (p_dest == NULL && p_src == NULL)
		return (p_dest);
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (p_dest);
}
