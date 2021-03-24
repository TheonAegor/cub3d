/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:19:11 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 15:37:04 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	my_mlx_get_color2(t_data data, int x, int y)
{
	char	*dst;

	dst = data.addr + (y * data.llen + x * (data.bpp / 8));
	return (*(unsigned int *)dst);
}

unsigned int	my_mlx_get_color(t_image_e data, int x, int y)
{
	char	*dst;

	dst = data.addr + (y * data.llen + x * (data.bpp / 8));
	return (*(unsigned int *)dst);
}

int				push_img_to_texture(char *path, int num, t_all *all)
{
	int x;
	int y;

	if ((all->image_e.img = mlx_xpm_file_to_image(all->vars.mlx,
		path, &all->image_e.img_w, &all->image_e.img_h)) == 0)
	{
		error_image(-1, all);
		return (-1);
	}
	all->image_e.addr = mlx_get_data_addr(all->image_e.img,
		&all->image_e.bpp, &all->image_e.llen, &all->image_e.end);
	x = 0;
	while (x < TW)
	{
		y = 0;
		while (y < TH)
		{
			all->texture[num][TW * y + x] =
				my_mlx_get_color(all->image_e, x, y);
			y++;
		}
		x++;
	}
	return (1);
}

void			draw_buffer(t_data *img, t_all *all)
{
	int x;
	int y;

	x = 0;
	while (x < all->w)
	{
		y = 0;
		while (y < all->h)
		{
			my_mlx_pixel_put(img, x, y, all->buffer[y][x]);
			y++;
		}
		x++;
	}
}

int				exit_but(t_all *all)
{
	free_all(all);
	exit(0);
	return (1);
}
