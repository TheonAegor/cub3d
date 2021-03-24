/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:13:55 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 08:24:58 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		define_directions(t_all *all)
{
	all->dx = 0;
	all->planey = 0;
	all->planex = 0;
	all->dy = 0;
	if (all->sow == 'N')
	{
		all->dy = -1;
		all->planex = 0.66;
	}
	else if (all->sow == 'S')
	{
		all->dy = 1;
		all->planex = -0.66;
	}
	else if (all->sow == 'E')
	{
		all->dx = 1;
		all->planey = 0.66;
	}
	else if (all->sow == 'W')
	{
		all->dx = -1;
		all->planey = -0.66;
	}
}

void		find_plr(t_all *all)
{
	push_img_to_texture(all->no, 0, all);
	push_img_to_texture(all->sou, 1, all);
	push_img_to_texture(all->we, 2, all);
	push_img_to_texture(all->ea, 3, all);
	push_img_to_texture(all->sp, 4, all);
	define_directions(all);
	count_sprites(all);
	create_spr_tabl(all);
}

void		new_pp(char **dst, int color)
{
	int i;

	i = 0;
	while (dst[i])
	{
		*(unsigned int*)(dst[i]) = color;
		i++;
	}
}

int			show_map(t_all *all)
{
	t_data		img;
	t_point		point;

	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, all->w, all->h, "test");
	all->img.img = mlx_new_image(all->vars.mlx, all->w, all->h);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp,
			&all->img.llen, &all->img.en);
	if (draw_screen_scale(all, &point, &all->img) < 0)
		return (-1);
	mlx_hook(all->vars.win, 2, (1L << 0), &key_press, all);
	mlx_hook(all->vars.win, 33, (0L << 0), &exit_but, all);
	mlx_loop(all->vars.mlx);
}
