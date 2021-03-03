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
	draw_plr(img, all->plr.x, all->plr.y, all->plr.angle);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}

void	draw_plr(t_data *img, float x, float y, float angle)
{
	char *dst;

//	my_mlx_pixel_put(img, x, y, 255);
	while (((int)y >= 0 && (int)y <= HEIGHT) && ((int)x >= 0 && (int)x <= WIDTH))
	{
//		printf("draw_plr||sin=%f,cos=%f\n", sin(angle_to_rad(angle)), cos(angle_to_rad(angle)));
//		printf("dst=%u\n", *(unsigned int*)dst);
//		printf("angl int draw_plr=%f\n", angle);
//		printf("rad=%f, cos=%f\n", angle_to_rad(angle), cos(angle_to_rad(angle)));
		dst = img->addr + ((int)y * img->llen + (int)x * img->bpp / 8);
//		printf("(%d;%d), %%=%d\n", (int)x, (int)y, ((int)x - START) % SCALE);
		if ((((((int)x - START) % SCALE) == 0) || ((((int)y - START) % SCALE) == 0)) && *(unsigned int*)dst == WALL)
			return ;
		pix_put_plr(img, x + 10/2, y + 10/2, 0xff0000);
		x -= cos(angle_to_rad(angle));
		y -= sin(angle_to_rad(angle));
//		printf("x=%d,y=%d, angle=%f\n", x,y, angle);
//		sleep(1);
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
	distributor(key, all);
	return (key);
}
