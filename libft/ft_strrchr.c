/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:35:35 by taegor            #+#    #+#             */
/*   Updated: 2020/11/22 13:48:44 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int i;
	int res;

	i = 0;
	res = -1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			res = i;
		i++;
	}
	if (res != -1)
		return ((char *)s + res);
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}
