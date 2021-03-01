#include "cub3d.h"

void	clear_img2(t_data *img, int w, int l)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= w)
	{
		y = 0;
		while (y <= l)
		{
			my_mlx_pixel_put(img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

float		angle_to_rad(float degree)
{
	float res;

	res = degree * (PI / 180);
	return (res);
}

void	distributor(int key, t_all *all)
{
	t_point point;
	int		time_s;

	point.x = START;
	point.y = START;
	if (key == W)
	{
		all->plr.y -= sin(angle_to_rad(all->plr.angle)) * 4;
		all->plr.x -= cos(angle_to_rad(all->plr.angle)) * 4;

//		printf("x=%f,y=%f, dir = %f, sin(y)=%f, cos(x)=%f\n", all->plr.x, all->plr.y, all->plr.angle, round(sin(angle_to_rad(all->plr.angle))) * 4, round(cos(angle_to_rad(all->plr.angle))) * 4);
	}
	if (key == A)
	{
		all->plr.angle -= 5;
		printf("angl=%f\n", all->plr.angle);
	}
	if (key == S)
	{
		all->plr.y += sin(angle_to_rad(all->plr.angle)) * 4;
		all->plr.x += cos(angle_to_rad(all->plr.angle)) * 4;

//		printf("x=%f,y=%f, dir = %f, sin(y)=%f, cos(x)=%f\n", all->plr.x, all->plr.y, all->plr.angle, round(sin(angle_to_rad(all->plr.angle))) * 4, round(cos(angle_to_rad(all->plr.angle))) * 4);
	}
	if (key == D)
	{
		all->plr.angle += 5;
		printf("angl=%f\n", all->plr.angle);
	}
	if (key == 65307)
		exit(0);
	clear_img2(&all->img, WIDTH, HEIGHT);
	draw_only_map_scale(all, &point, &all->img);
//	draw_plr(&all->img, all->plr.x, all->plr.y, all->plr.angle);
	draw_plr_scale(&all->img, all->plr.x, all->plr.y, PLR);
	draw_plr(&all->img, all->plr.x, all->plr.y, all->plr.angle);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}
