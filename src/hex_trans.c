/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_trans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:00:22 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 15:57:36 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				check_edges(t_all *all, char *rgb)
{
	int				i;

	i = 0;
	if ((ft_atoi(&rgb[i])) < 0 || ft_atoi(&rgb[i]) > 255)
	{
		error_big_color(all);
		return (-1);
	}
	while (rgb[i] != ',' && rgb[i])
		i++;
	i++;
	if ((ft_atoi(&rgb[i])) < 0 || ft_atoi(&rgb[i]) > 255)
	{
		error_big_color(all);
		return (-1);
	}
	while (rgb[i] != ',' && rgb[i])
		i++;
	i++;
	if ((ft_atoi(&rgb[i])) < 0 || ft_atoi(&rgb[i]) > 255)
	{
		error_big_color(all);
		return (-1);
	}
	return (1);
}

int				check_hex(t_all *all)
{
	if (check_chars(all->floor_c) == -1)
	{
		handle_hex_err2(-1, all);
		return (-1);
	}
	if (check_chars(all->ceil_c) == -1)
	{
		handle_hex_err2(-2, all);
		return (-1);
	}
	if (check_commas(all->floor_c, all) < 0 ||
			check_commas(all->ceil_c, all) < 0)
		return (-1);
	if (check_edges(all, all->floor_c) < 0 ||
			check_edges(all, all->ceil_c) < 0)
		return (-1);
	return (1);
}

int				check_commas(char *str, t_all *all)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
			counter++;
		i++;
	}
	if (counter < 2)
	{
		handle_hex_err2(-3, all);
		return (-1);
	}
	if (counter > 2)
	{
		handle_hex_err2(-4, all);
		return (-1);
	}
	return (1);
}

int				check_chars(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(ft_strchr("0123456789, \0\t", str[i])))
			return (-1);
		i++;
	}
	return (1);
}

unsigned		to_hex(char *rgb)
{
	int				i;
	unsigned long	res;

	i = 0;
	res = ft_atoi(&rgb[i]) << 16;
	while (rgb[i] != ',' && rgb[i])
		i++;
	i++;
	res += ft_atoi(&rgb[i]) << 8;
	while (rgb[i] != ',' && rgb[i])
		i++;
	i++;
	res += ft_atoi(&rgb[i]);
	return (res);
}
