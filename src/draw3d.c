#include "cub3d.h"

void draw_lines(t_data *img, int ds, int de, int x, int color)
{
	while (ds < de)
	{
		my_mlx_pixel_put(img, x, ds, color);
		ds++;
	}
}
/*
void draw_the_line2(t_data *img, float px, float py, float rx, float ry)

{
	float tang;

	tang = fabs((py-ry)/(px - rx));
//	printf("tang=%f\n", tang);
//	printf("p(%f;%f):r(%f;%f)\n", px,py,rx,ry);
	if (py > ry)
	{
		if (px > rx)
		{
			while((int)px != (int)rx && ((int)px >= 0 && (int)py > 0))
			{
				my_mlx_pixel_put(img, (int)px, (int)py, 0xff0000);
				py -= tang;
				px--;
				printf("p(%f;%f):r(%f;%f)\n", px,py,rx,ry);
			}
		}
		else
		{
			while((int)px != (int)rx && ((int)px >= 0 && (int)py > 0))
			{
				my_mlx_pixel_put(img, (int)px, (int)py, 0xff0000);
				py -= -tang;
				px++;
//				printf("p(%f;%f):r(%f;%f)\n", px,py,rx,ry);
			}
		}
	}
	else 
	{
		if (px > rx)
		{
			while((int)px != (int)rx && ((int)px >= 0 && (int)py >= 0))
			{
				my_mlx_pixel_put(img, (int)px, (int)py, 0xff0000);
				py -= tang;
				px--;
			}
		}
		else
		{
			while((int)px != (int)rx && ((int)px >= 0 && (int)py >= 0) )
			{
				my_mlx_pixel_put(img, (int)px, (int)py, 0xff0000);
				py -= -tang;
				px++;
			}
		}
	}
}
*/

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
	scale_x = x +WIDTH/2/12;
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

float	dist(float x, float y, float xx, float yy)
{
	return (hypotf(fabs(x - xx), fabs(y -yy)));
}
