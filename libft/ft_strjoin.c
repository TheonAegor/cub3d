/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:38:31 by taegor            #+#    #+#             */
/*   Updated: 2020/11/22 13:56:46 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*p;
	int			len_s1;
	int			len_s2;
	int			i;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(p = ft_calloc((len_s1 + len_s2 + 1), sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len_s1)
	{
		p[i] = s1[i];
	}
	i = -1;
	while (++i < len_s2)
	{
		p[i + len_s1] = s2[i];
	}
	p[len_s1 + len_s2] = '\0';
	return (p);
}
