/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:54:41 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 08:54:42 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_hex_err2(int err, t_all *all)
{
	free_map(all);
	ft_printf("Error!\n");
	if (err == -1)
		ft_printf("You have forbidden chars in your Floor initialization\n");
	if (err == -2)
		ft_printf("You have forbidden chars in your Ceil initialization\n");
	if (err == -3)
		ft_printf("You don't have R or G or B value\n");
	if (err == -4)
		ft_printf("You have extra value in Floor or Ceil initialization\n");
}

void	error_forbid_char(t_all *all)
{
	free_map(all);
	ft_printf("Error!\n");
	ft_printf("You have used forbidden char in your map\n");
}
