/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:57:39 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 17:24:52 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		handle_arg_errors(int error)
{
	ft_printf("Error!\n");
	if (error < 2)
		ft_printf("Please, add a map, user\n");
	if (error > 3)
		ft_printf("You added to much arguments\n");
}

void		handle_plr_errors(int error, t_all *all)
{
	free_map(all);
	ft_printf("Error!\n");
	if (error == 0)
		ft_printf("You don't have a player position\n");
	if (error > 1)
		ft_printf("You have several player positions\n");
}

void		handle_map_errors(int x, int y, t_all *all)
{
	free_map(all);
	ft_printf("Error!\n");
	ft_printf("You'r map is not closed. Check point (%d,%d)\n", x, y);
}

void		handle_parse_err(int err, t_all *all)
{
	free_map(all);
	ft_printf("Error!\n");
	if (err == 157)
		ft_printf("Texture for North side exist's no\n");
	else if (err == -23)
		ft_printf("Resolution is incorrect\n");
	else if (err == 162)
		ft_printf("Texture for South side exist's no\n");
	else if (err == 156)
		ft_printf("Texture for Weast side exist's no\n");
	else if (err == 134)
		ft_printf("Texture for East side exist's no\n");
	else if (err == 115)
		ft_printf("Sprite file can't be open\n");
	else if (err == -1)
		ft_printf("You may initialize only 1 elem 1 time\n");
	else if (err > 709)
		ft_printf("You have extra conditions in you map\n");
	else if (err < 709)
		ft_printf("You don't have all needed element before your map\n");
}

void		handle_hex_err(int err, t_all *all)
{
	free_map(all);
	ft_printf("Error!\n");
	if (err == -1)
		ft_printf("You have more the 3 digits to you F or C color\n");
}
