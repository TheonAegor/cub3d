/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:15:27 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 16:29:38 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int			draw_screen_scale(t_all *all)
{
	if (find_plr(all) == -1)
		return (-1);
	middle_init(all);
	draw_plr2(all);
	if (all->save == 1)
	{
		screen_shot(all);
		free_all(all);
		return (-1);
	}
	mlx_do_sync(all->vars.mlx);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	return (1);
}

int			parse_map(t_all *all)
{
	int	err;
	int	i;
	int	full;

	i = -1;
	full = 0;
	start_init(all);
	while (all->map[++i])
	{
		err = parse_elems(all, &full, i);
		if (err != 1)
		{
			handle_parse_err(err, all);
			return (-1);
		}
	}
	if (help_with_hex(all, full) == -1)
		return (-1);
	return (err);
}

void		draw_plr2(t_all *all)
{
	t_dda		dda;
	t_spr_cast	s;

	dda.x = 0;
	while (dda.x < all->w)
	{
		start_dda(&dda, all);
		find_side(&dda, all);
		find_hit(&dda, all);
		find_start_end(&dda, all);
		determine_num_texture(&dda, all);
		wall_and_text(&dda, all);
		fill_buf(&dda, all);
	}
	precasting(all);
	s.i = 0;
	while (s.i < all->spr.num_spr)
	{
		spr_cast1(&s, all);
		spr_cast2(&s, all);
		s.i++;
	}
	draw_buffer(&all->img, all);
	clear_buffer(all);
}

int			key_press(int key, t_all *all)
{
	distributor(key, all);
	return (key);
}
