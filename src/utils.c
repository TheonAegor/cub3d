#include "cub3d.h"

void		my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
//	printf("dst=%u\n", dst);
//	printf("img.addr%i\n", img->addr);
	*(unsigned int*)dst = color;
}

void		pix_put_plr(t_data *img, float x, float y, int color)
{
	char *dst;
	int xx;
	int yy;

	xx = (int)round(x);
	yy = (int)round(y);
	dst = img->addr + (yy * img->llen + xx * (img->bpp / 8));
//	printf("dst=%u\n", dst);
//	printf("img.addr%i\n", img->addr);
	*(unsigned int*)dst = color;
}

int		draw_screen_scale(t_all *all, t_point *point, t_data *img)
{
	draw_map_scale(all, point, img);
/*
-------------Нарисовать игрока отдельно------------------------
*/
	draw_plr(img, all->plr.x, all->plr.y, all->plr.angle, all);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}

void	draw_plr(t_data *img, float x, float y, float angle, t_all *all)
{
	char *dst;
	float ang_rng_top;
	float ang_rng_low;
	float xx;
	float yy;
	int distt;
	float line_h;
	float line_h_end;
	int iter;

	ang_rng_top = angle + VIEW/2;
	ang_rng_low = angle - VIEW/2;
	xx = x;
	yy = y;
	line_h = 0;
	line_h_end = 1000;
	iter = 0;

	while (ang_rng_low < ang_rng_top)
	{
		xx = x;
		yy = y;
		while (xx < WIDTH && yy < WIDTH)
		{
			dst = img->addr + ((int)yy * img->llen + (int)xx * img->bpp / 8);
			if (all->map[(int)(floor(yy/SCALE))][(int)(floor(xx/SCALE))] == '1')
			{
				printf("xx=%f, yy=%f", xx, yy);
				distt = HEIGHT / dist(x, y, xx, yy);
				printf("%d\n", distt);
				draw_the_line(img, &iter, angle, distt, all);
				iter++;
				break ;
			}
			pix_put_plr(img, xx, yy, 0xff0000);
			xx -= cos(angle_to_rad(ang_rng_low));
			yy -= sin(angle_to_rad(ang_rng_low));
		}
		ang_rng_low += 0.5;
	}
/*
*/

}

void	draw_plr_scale(t_data *img, float x, float y, int color)
{
	int scale_y;
	int scale_x;

//	printf("x = %f, y= %f, SCALE = %d, col = %d\n", x, y, SCALE, color);
	scale_y = y + 10;
	scale_x = x + 10;
//	printf("scl_x=%d, scl_y=%d\n", scale_x, scale_y);
	while ((int)y < scale_y)
	{
		while ((int)x < scale_x)
		{
			pix_put_plr(img, x, y, color);
			x++;
		}
		x = x - 10;
		y++;
	}

}

int		key_press(int key, t_all *all)
{
	printf("%d\n", key);
	distributor(key, all);
	return (key);
}
