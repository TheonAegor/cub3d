/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:27:26 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 09:27:27 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			create_spr_tabl(t_all *all)
{
	int x;
	int y;
	int i;

	all->sprite = ft_calloc(sizeof(t_sprite), (all->spr.num_spr));
	y = all->brd.map_row;
	i = 0;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[y][x] == '2')
			{
				all->sprite[i].x = (double)x + 0.5;
				all->sprite[i].y = (double)y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

void		count_sprites(t_all *all)
{
	int x;
	int y;

	all->spr.num_spr = 0;
	y = all->brd.map_row;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (all->map[y][x] == '2')
				all->spr.num_spr++;
			x++;
		}
		y++;
	}
}

static void	sort_sprites2(t_sprites *sprites, t_all *all)
{
	int		i;
	int		j;
	double	tmp_dist;
	int		tmp_order;

	j = 0;
	while (j < all->spr.num_spr / 2 + 1)
	{
		i = 0;
		while (i < all->spr.num_spr - 1)
		{
			if (sprites[i].first < sprites[i + 1].first)
			{
				tmp_dist = sprites[i].first;
				tmp_order = sprites[i].second;
				sprites[i].first = sprites[i + 1].first;
				sprites[i].second = sprites[i + 1].second;
				sprites[i + 1].first = tmp_dist;
				sprites[i + 1].second = tmp_order;
			}
			i++;
		}
		j++;
	}
}

void		sort_sprites(int *so, double *sd, t_all *all)
{
	int			i;
	t_sprites	sprites[all->spr.num_spr];

	i = 0;
	while (i < all->spr.num_spr)
	{
		sprites[i].first = sd[i];
		sprites[i].second = so[i];
		i++;
	}
	sort_sprites2(sprites, all);
	i = 0;
	while (i < all->spr.num_spr)
	{
		all->sd[i] = sprites[i].first;
		all->so[i] = sprites[i].second;
		i++;
	}
}
