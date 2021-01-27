/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 13:22:00 by taegor            #+#    #+#             */
/*   Updated: 2020/11/14 20:09:23 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (!s1 && !s2)
		return (0);
	while (ps1[i] == ps2[i] && --n > 0)
		i++;
	if (ps1[i] == '\0' && ps2[i] == '\0')
		return (0);
	if (n == 0)
		return (0);
	return (ps1[i] - ps2[i]);
}
