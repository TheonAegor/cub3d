/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:54:41 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 15:33:37 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_hex_err2(int err, t_all *all)
{
	free_map(all);
	printf("Error!\n");
	if (err == -1)
		printf("You have forbidden chars in your Floor initialization\n");
	if (err == -2)
		printf("You have forbidden chars in your Ceil initialization\n");
	if (err == -3)
		printf("You don't have R or G or B value\n");
	if (err == -4)
		printf("You have extra value in Floor or Ceil initialization\n");
}

void	error_forbid_char(t_all *all)
{
	free_map(all);
	printf("Error!\n");
	printf("You have used forbidden char in your map\n");
}

void	error_filename(int err)
{
	printf("Error!\n");
	if (err == -1)
		printf("You'r filename is too short\n");
	if (err == -2)
		printf("You'r filename has wrong extension\n");
}

void	error_image(int err, t_all *all)
{
	free_map(all);
	printf("Error!\n");
	if (err == -1)
		printf("Image for wall or sprite is invalid\n");
}
