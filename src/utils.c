#include "cub3d.h"

int		change_direction(t_data *img, int x, int y, int scale)
{
	int scale_y;
	int scale_x;

	scale_y = y + scale;
	scale_x = x + scale;
	while (y < scale_y)
	{
		while (x < scale_x)
		{
			my_mlx_pixel_put(img, x, y, 0x000000);
			x++;
		}
		x = x - scale;
		y++;
	}
	return (1);
}

int		clear_img(t_data *img, int w, int l)
{
	int x;
	int y;

	x = 100;
	printf("%d, %d\n", x, w);
	while (x < w)
	{
		y = 100;
		while(y++ < l)
		{
			printf("%d, %d\n", y, l);
			my_mlx_pixel_put(img, x, y, 0x000000);
//			y++;
		}
		x++;
	}
	printf("cleared\n");
	return (1);
}

void		my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	printf("here_in_mmpp\n");
}

void	draw_plr(t_data *img, int x, int y)
{
	my_mlx_pixel_put(img, x, y, 255);
}

void	draw_plr_scale(t_data *img, int x, int y, int scale)
{
	int scale_y;
	int scale_x;

	scale_y = y + scale;
	scale_x = x + scale;
	while (y < scale_y)
	{
		while (x < scale_x)
		{
			my_mlx_pixel_put(img, x, y, 255);
			x++;
		}
		x = x - scale;
		y++;
	}
	printf("hereplr\n");
}

int		draw_screen_scale(t_all *all, t_point *point, t_data *img)
{
	draw_map_scale(all, point, img);
/*
-------------Нарисовать игрока отдельно------------------------
*/
	draw_plr_scale(img, all->plr.x, all->plr.y, 30);
/*
-------------Отправить картинку на экран-----------------------
*/
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
	sleep(5);
	change_direction(img, all->plr.x, all->plr.y, 30);
}

int		key_press(int key, t_all *all)
{
	printf("Key:%d\n", key);
/*
	clear_win(&all->img, 640, 480);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
	if (key == 65362)
		all->plr.x -= 30;
	else
		return (0);
	my_mlx_pp_scale(&all->img, &all->point, 0xFFFFFF, 30);
	draw_plr_scale(&all->img, all->plr.x, all->plr.y, 30);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
*/
}

int		clear_win(t_all *all, int w, int l)
{
	clear_img(&all->img, w, l);
/*
	mlx_destroy_window(all->vars.mlx, all->vars.win);
	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, 640, 480, "test2");
*/
//	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
//	mlx_loop(all->vars.mlx);
}
