/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:58:02 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 17:24:35 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		error_big_color(t_all *all)
{
	free_map(all);
	printf("Error\n");
	printf("You can put only value from 0-255\n");
}
