/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:52:25 by taegor            #+#    #+#             */
/*   Updated: 2020/11/21 13:17:17 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tens(int n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static int	ft_sqrt(int num, int i)
{
	while (i > 0)
	{
		num = num * 10;
		i--;
	}
	return (num);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		tens;
	int		step;
	char	dig[1];

	if (n == 0)
		write(fd, "0", 1);
	if (n == -2147483648)
	{
		write(fd, "-2", 2);
		n = 147483648;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	tens = ft_tens(n);
	while (tens-- > 0)
	{
		step = ft_sqrt(1, tens);
		dig[0] = (n / step + 48);
		write(fd, &dig[0], 1);
		n = n - (n / step) * step;
	}
}
