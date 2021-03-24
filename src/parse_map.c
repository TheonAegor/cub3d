/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:10:39 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 17:27:35 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_elems(t_all *all, int *full, int i)
{
	int err;

	err = 1;
	if (all->map[i][0] == 'R')
		err = parse_r(all->map[i], full, all);
	if (all->map[i][0] == 'N' && all->map[i][1] == 'O')
		err = parse_side(all->map[i], &all->no, full, 0);
	if (all->map[i][0] == 'S' && all->map[i][1] == 'O')
		err = parse_side(all->map[i], &all->sou, full, 0);
	if (all->map[i][0] == 'W' && all->map[i][1] == 'E')
		err = parse_side(all->map[i], &all->we, full, 0);
	if (all->map[i][0] == 'E' && all->map[i][1] == 'A')
		err = parse_side(all->map[i], &all->ea, full, 0);
	if (all->map[i][0] == 'S' && all->map[i][1] != 'O')
		err = parse_side(all->map[i], &all->sp, full, 0);
	if (all->map[i][0] == 'F')
		err = parse_side(all->map[i], &all->floor_c, full, 1);
	if (all->map[i][0] == 'C')
		err = parse_side(all->map[i], &all->ceil_c, full, 1);
	if (*full == 8)
	{
		all->brd.map_row = i + 1;
		(*full) += 1;
	}
	return (err);
}

int		help_with_hex(t_all *all, int full)
{
	if (full != 9)
	{
		handle_parse_err(full + 700, all);
		return (-1);
	}
	if (check_hex(all) == -1)
		return (-1);
	all->color.floor = to_hex(all->floor_c);
	all->color.ceil = to_hex(all->ceil_c);
	if (all->color.floor == 1 || all->color.ceil == 1)
	{
		handle_hex_err(-1, all);
		return (-1);
	}
	return (1);
}

int		parse_r(char *res, int *full, t_all *all)
{
	int i;
	int ww;
	int hh;

	i = 1;
	if (all->w != -1 || all->h != -1)
		return (-1);
	all->w = ft_atoi(&res[i]);
	while (res[i] == ' ')
		i++;
	while (ft_isdigit(res[i]))
		i++;
	all->h = ft_atoi(&res[i]);
	if (all->w <= 0 || all->h <= 0)
		return (-23);
	all->w = all->w;
	all->vars.mlx = mlx_init();
	mlx_get_screen_size(all->vars.mlx, &ww, &hh);
	if (all->w > ww || all->h > hh)
		mlx_get_screen_size(all->vars.mlx, &all->w, &all->h);
	*full += 1;
	return (1);
}

int		parse_side(char *path, char **side, int *full, int flag)
{
	int	i;
	int	err;

	i = 2;
	err = 1;
	if (*side != NULL)
		return (-1);
	while (path[i] == ' ')
		i++;
	if (flag == 0)
	{
		err = open(&path[i], O_RDONLY);
		if (err < 0)
			return (path[0] + path[1]);
		close(err);
	}
	else
		i = 1;
	*side = &path[i];
	*full += 1;
	return (1);
}
