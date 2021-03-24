/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_smth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:58:07 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 08:58:08 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_all *all)
{
	int i;

	i = 0;
	while (all->map[i])
	{
		free(all->map[i]);
		i++;
	}
	free(all->map);
}

void	free_buf_z(t_all *all)
{
	int i;

	i = 0;
	while (i < all->h)
	{
		free(all->buffer[i]);
		i++;
	}
	free(all->buffer);
	free(all->zbuf);
}

void	free_all(t_all *all)
{
	free_map(all);
	free_buf_z(all);
}
