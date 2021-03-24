/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:28:08 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 09:28:08 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		start_init(t_all *all)
{
	all->w = -1;
	all->h = -1;
}

void		middle_init(t_all *all)
{
	int i;

	all->buffer = ft_calloc(sizeof(unsigned *), all->h);
	i = 0;
	while (i < all->h)
	{
		all->buffer[i] = ft_calloc(sizeof(unsigned), all->w);
		i++;
	}
	all->zbuf = ft_calloc(sizeof(double*), all->w);
}
