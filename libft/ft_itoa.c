/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:37:22 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 16:26:03 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_find_tens(int n)
{
	int				i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	if (n == 0 && i == 0)
		i = 1;
	return (i);
}

static char			*ft_ifbigger(char *p, int tens,
		long long int n)
{
	if (!(p = ft_calloc(sizeof(char), tens + 1)))
		return (NULL);
	p[tens--] = '\0';
	while (tens >= 0)
	{
		p[tens] = n % 10 + 48;
		n /= 10;
		tens--;
	}
	return (p);
}

char				*ft_itoa(int num)
{
	char			*p;
	int				tens;
	long long int	n;

	p = NULL;
	n = (long int)num;
	tens = ft_find_tens(n);
	if (n >= 0)
		p = ft_ifbigger(p, tens, n);
	else
	{
		if (!(p = ft_calloc(sizeof(char), tens + 2)))
			return (NULL);
		tens += 1;
		n = (-1) * n;
		p[tens--] = '\0';
		while (tens > 0)
		{
			p[tens] = n % 10 + 48;
			n /= 10;
			tens--;
		}
		p[tens] = '-';
	}
	return (p);
}
