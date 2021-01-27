/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:27:59 by taegor            #+#    #+#             */
/*   Updated: 2020/11/25 19:17:34 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src,
		size_t size)
{
	size_t		result_len;
	size_t		i;

	if (!dst || !src)
		return (0);
	result_len = ft_strlen(src);
	if (size == 0)
		return (result_len);
	i = 0;
	while (size - 1 > i && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (result_len);
}
