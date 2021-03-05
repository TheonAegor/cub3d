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
	int iter;

	ang_rng_top = angle + VIEW/2;
	ang_rng_low = angle - VIEW/2;
	xx = x;
	yy = y;
//	draw3D(all);
//	my_mlx_pixel_put(img, x, y, 255);
	iter = 0;
	while (ang_rng_low < ang_rng_top)
	{	
		x = xx;
		y = yy;
		while (((int)y >= 0 && (int)y <= HEIGHT) && ((int)x >= 0 && (int)x <= WIDTH))
		{
			dst = img->addr + ((int)y * img->llen + (int)x * img->bpp / 8);
			if (*(unsigned int*)dst == WALL)
			{
/*
*/
				distt = dist(x, y, xx, yy);
//				printf("after distt, %d\n", SCALE * HEIGHT);
				if (distt <= 0)
					distt = 1;
				line_h = (int)((SCALE * 700) / distt);
//				printf("after line_h\n");
				if (line_h > HEIGHT)
					line_h = HEIGHT;
				printf("line_h=%f\n", line_h);
				draw_the_line(&all->img, &iter, angle, line_h, all);
				break ;
			}
			pix_put_plr(img, x, y, 0xff0000);
			x -= cos(angle_to_rad(ang_rng_low));
			y -= sin(angle_to_rad(ang_rng_low));
		}
		ang_rng_low += 1;
		printf("iter=%d\n", iter);
	}
	printf("here\n");
//	mlx_hook(all->game.vars.win, 2, (1L << 0), &key_press, all);
//	mlx_loop(all->game.vars.mlx);
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
	distributor(key, all);
	return (key);
}
