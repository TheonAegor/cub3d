#include "cub3d.h"

unsigned int    my_mlx_get_color(t_image_e data, int x, int y)
{
        char    *dst;

        dst = data.addr + (y * data.llen + x * (data.bpp / 8));
        return (*(unsigned int *)dst);
}

void			push_img_to_texture(char *path, int num, t_all *all)
{
	int x;
	int y;

	all->image_e.img = mlx_xpm_file_to_image(all->vars.mlx, path, &all->image_e.img_w, &all->image_e.img_h);
	all->image_e.addr = mlx_get_data_addr(all->image_e.img, &all->image_e.bpp, &all->image_e.llen, &all->image_e.end);
	x = 0;
	while (x < TW)
	{
		y = 0;
		while (y < TH)
		{
			all->texture[num][TW * y +x] = my_mlx_get_color(all->image_e, x, y);
			y++;
		}
		x++;
	}
}


void	find_plr(t_all *all)
{

	push_img_to_texture(all->no, 0, all);
	push_img_to_texture(all->sou, 1, all);
	push_img_to_texture(all->we, 2, all);
	push_img_to_texture(all->ea, 3, all);
	push_img_to_texture(all->sp, 4, all);
	if (all->sow == 'N')
	{
		all->dx = 0;
		all->dy = -1;
		all->planex = 0.66;
		all->planey = 0;
	}
	else if (all->sow == 'S')
	{
		all->dx = 0;
		all->dy = 1;
		all->planex = -0.66;
		all->planey = 0;
		
	}
	else if (all->sow == 'E')
	{
		all->dx = 1;
		all->dy = 0;
		all->planex = 0;
		all->planey = 0.66;
	}	
	else if (all->sow == 'W')
	{
		all->dx = -1;
		all->dy = 0;
		all->planex = 0;
		all->planey = -0.66;

	}
	count_sprites(all);
	create_spr_tabl(all);
}

void draw_buffer(t_data *img, t_all *all)
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


void	new_pp(char **dst, int color)
{
	int i;
	
	i =0;
	while (dst[i])
	{
		*(unsigned int*)(dst[i]) = color;
		i++;
	}
}

int exit_but(t_all *all)
{
	exit(0);
	return (1);
}

int		show_map(t_all *all)
{
	t_data		img;
	t_point		point;

//	if (parse_map(all) < 0)
//		return (-1);
	all->point.x = 100;
	all->point.y = 100;
	point.x = 100;
	point.y = 100;
//	printf("%d,%d\n", all->plr.x, all->plr.y);	
	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, all->w, all->h, "test");
	all->img.img = mlx_new_image(all->vars.mlx, all->w, all->h);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.llen, &all->img.en);
//	draw3D(all);
	if(!(draw_screen_scale(all, &point, &all->img)))
		return (-1);
	mlx_hook(all->vars.win, 2, (1L << 0), &key_press, all);
	mlx_hook(all->vars.win, 33, (0L << 0), &exit_but, all);
//	mlx_loop(all->game.vars.mlx);
	mlx_loop(all->vars.mlx);
}
