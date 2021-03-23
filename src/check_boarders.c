/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boarders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:31:09 by taegor            #+#    #+#             */
/*   Updated: 2021/03/23 23:31:10 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			if_forbid_chars(int c, char *forbid_chars)
{
	int i;

	i = 0;
	while (forbid_chars[i])
	{
		if (c == forbid_chars[i])
			return (1);
		i++;
	}
	return (-1);
}

int			if_nswe(t_all *all, int i, int j, int *flag)
{
	if (ft_strchr("NSWE", all->map[i][j]))
	{
		all->sow = all->map[i][j];
		all->plr.x = (double)j + 0.5;
		all->plr.y = (double)i + 0.5;
		all->map[i][j] = '0';
		(*flag) += 1;
	}
	if (if_forbid_chars(all->map[i][j], "NSWE 012\n\t\0") == -1)
	{
		error_forbid_char(all);
		return (-1);
	}
	return (1);
}

int			find_only_plr(t_all *all)
{
	int i;
	int j;
	int flag;

	i = all->brd.map_row;
	flag = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (if_nswe(all, i, j, &flag) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (flag != 1)
	{
		handle_plr_errors(flag, all);
		return (-1);
	}
	return (1);
}

static int	check_neighbors(t_all *all, int y, int x)
{
	if (all->map[y + 1])
	{
		if (all->map[y + 1][x] == ' ' || x - 1 < 0 ||
				ft_strchr(" \0", all->map[y + 1][x + 1]) ||
				ft_strchr(" \0", all->map[y + 1][x - 1]))
			return (-1);
	}
	else
		return (-1);
	if (all->map[y - 1])
	{
		if (all->map[y - 1][x] == ' ' || x - 1 < 0 ||
				ft_strchr(" \0", all->map[y - 1][x + 1]) ||
				ft_strchr(" \0", all->map[y - 1][x - 1]))
			return (-1);
	}
	else
		return (-1);
	return (1);
}

int			check_bounds2(t_all *all, t_brd *brd)
{
	int y;
	int x;
	int res;

	y = brd->map_row;
	res = 0;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (ft_strchr("NSWE02", all->map[y][x]))
			{
				res = check_neighbors(all, y, x);
				if (res < 0)
				{
					handle_map_errors(x, y, all);
					return (res);
				}
			}
			x++;
		}
		y++;
	}
	return (res);
}
