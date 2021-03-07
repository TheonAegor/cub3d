#include "cub3d.h"

void draw_the_line(t_data *img, int *iter, float line_h, t_all *all, int color)
{
	int x;
	int scale_x;
	int y;
/*
	x = (int)(base_ang - angle);
	if (x <= 0)
		x = (int)(angle + (base_ang - angle));
	printf("x int draw_the_line=%d\n", x);	
*/
	x = *iter + WIDTH/2;
	scale_x = x + WIDTH/2/120;
	*iter += scale_x - x;
/*
	while (x < scale_x)
	{
		y = 0;
		while (y < 150)
			my_mlx_pixel_put(img, x, y++, 0xffffff);
		x++;
	}
	x = *iter;
*/
	while (x < scale_x)
	{
		int tmp;

		y = HEIGHT / 2;
		tmp = y + (int)line_h/2;
		while (y < tmp)
		{
			my_mlx_pixel_put(img, x, y++, color);
		}
		y = HEIGHT / 2;
		tmp = y - (int)line_h/2;
		while (y > tmp)
			my_mlx_pixel_put(img, x, y--, color);
		x++;
	}
//	printf("iter=%d\n", *iter);
//	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0); 
}

void draw3D(t_all *all)
{

	all->game.vars.mlx = mlx_init();
	all->game.vars.win = mlx_new_window(all->game.vars.mlx, WIDTH, HEIGHT, "game");
	all->game.img.img = mlx_new_image(all->game.vars.mlx, WIDTH, HEIGHT);
	all->game.img.addr = mlx_get_data_addr(all->game.img.img, &all->game.img.bpp, &all->game.img.llen, &all->game.img.en);
/*
	all->game.line_h = (SCALE*HEIGHT)/distt;
	if (all->game.line_h > HEIGHT)
		all->game.line_h = HEIGHT;
	draw_the_line(&all->game.img, lall->game.ine_h, base_ang, angle, &vars);
//	mlx_loop(all->game.vars.mlx);
*/
		
}

float	dist(float x, float y, float xx, float yy)
{
	return (hypotf(fabs(x - xx), fabs(y -yy)));
}
