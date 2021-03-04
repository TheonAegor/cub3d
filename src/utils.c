#include "cub3d.h"

draw_the_line(t_data *img, float line_h, float base_ang, float angle, t_vars *vars)
{
	int x;
	int scale_x;
	int y;

	x = base_ang - angle;
	if (x <= 0)
		x = angle + (base_ang - angle);	
	y = 0;
	scale_x = x + 8;
	while (x < scale_x)
	{
		while (y < line_h)
			my_mlx_pixel_put(img, x, y++, 0xff0000);
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->img,0, 0); 
	
	
}

void draw3D(float distt, float base_ang, float angle)
{
	t_vars vars;
	t_data img;
	float line_h;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "game");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.en);
	line_h = (SCALE*HEIGHT)/distt;
	if (line_h > HEIGHT)
		line_h = HEIGHT;
	draw_the_line(&img, line_h, base_ang, angle, &vars);
	mlx_loop
		
}

int		dist(float x, float y, float xx, float yy)
{
	return (hypotf(fabs(x - xx), fabs(y -yy)));
}
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
	int	ang_rng_top;
	int ang_rng_low;
	float xx;
	float yy;
	int distt;

	ang_rng_top = angle + 30;
	ang_rng_low = angle - 30;
	xx = x;
	yy = y;
//	my_mlx_pixel_put(img, x, y, 255);
	while (ang_rng_low < ang_rng_top)
	{	
		x = xx;
		y = yy;
		while (((int)y >= 0 && (int)y <= HEIGHT) && ((int)x >= 0 && (int)x <= WIDTH))
		{
			dst = img->addr + ((int)y * img->llen + (int)x * img->bpp / 8);
			if (*(unsigned int*)dst == WALL)
			{
				distt = dist(x, y, xx, yy);
				draw3D(distt, ang_rng_low, angle);
				break ;
			}
			pix_put_plr(img, x, y, 0xff0000);
			x -= cos(angle_to_rad(ang_rng_low));
			y -= sin(angle_to_rad(ang_rng_low));
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
	distributor(key, all);
	return (key);
}
