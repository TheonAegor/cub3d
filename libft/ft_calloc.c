/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 18:49:55 by taegor            #+#    #+#             */
/*   Updated: 2020/11/20 21:46:26 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	int		i;
	int		res;

	res = nmemb * size;
	i = 0;
	if (!(p = malloc(nmemb * size)))
		return (NULL);
	while (res--)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
