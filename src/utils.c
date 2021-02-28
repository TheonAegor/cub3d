#include "cub3d.h"

int		change_direction(t_data *img, int x, int y)
{
	int scale_y;
	int scale_x;

	scale_y = y + SCALE;
	scale_x = x + SCALE;
	while (y < scale_y)
	{
		while (x < scale_x)
		{
			my_mlx_pixel_put(img, x, y, 0x000000);
			x++;
		}
		x = x - SCALE;
		y++;
	}
	return (1);
}

int		clear_img(t_data *img, int w, int l)
{
	int x;
	int y;

	x = 100;
//	printf("%d, %d\n", x, w);
	while (x < w)
	{
		y = 100;
		while(y++ < l)
		{
//			printf("%d, %d\n", y, l);
			my_mlx_pixel_put(img, x, y, 0x000000);
//			y++;
		}
		x++;
	}
//	printf("cleared\n");
	return (1);
}

void		my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
//	printf("dst=%u\n", dst);
//	printf("img.addr%i\n", img->addr);
	*(unsigned int*)dst = color;
}

void	draw_plr(t_data *img, int x, int y)
{
	my_mlx_pixel_put(img, x, y, 255);
}

void	draw_plr_scale(t_data *img, int x, int y, int color)
{
	int scale_y;
	int scale_x;

	printf("x = %d, y= %d, SCALE = %d, col = %d\n", x, y, SCALE, color);
	scale_y = y + SCALE;
	scale_x = x + SCALE;
	while (y < scale_y)
	{
		while (x < scale_x)
		{
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		x = x - SCALE;
		y++;
	}

}

int		draw_screen_scale(t_all *all, t_point *point, t_data *img)
{
	draw_map_scale(all, point, img);
/*
-------------Нарисовать игрока отдельно------------------------
*/
	draw_plr_scale(img, all->plr.x, all->plr.y, 255);
/*
-------------Отправить картинку на экран-----------------------
*/
	release_ray(all);
//	draw_line(all);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}

int		key_press(int key, t_all *all)
{
	distributor(key, all);
	
//	printf("Key:%i, img.addr=%d\n", key, all->img.addr);
/*
	if (key = W)
	{
		draw_plr_scale(&all->img, all->plr.x, all->plr.y, SCALE, BLACK);
		mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
		all->plr.y++;
		draw_plr_scale(&all->img, all->plr.x, all->plr.y, SCALE, BLACK);
	}
*/
	return (key);
}

int		clear_win(t_all *all, int w, int l)
{
	clear_img(&all->img, w, l);
}
