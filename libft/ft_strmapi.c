/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:29:31 by taegor            #+#    #+#             */
/*   Updated: 2020/11/20 21:44:20 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	s_len;
	char			*p;
	int				i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (!(p = ft_calloc(sizeof(char), s_len + 1)))
		return (NULL);
	i = 0;
	while (s_len > 0)
	{
		p[i] = (f)(i, s[i]);
		i++;
		s_len--;
	}
	p[i] = '\0';
	return (p);
}
