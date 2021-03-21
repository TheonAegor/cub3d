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
	while (degree > 360)
		degree -= 360;

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
/*
		if (all->map[(int)(all->plr.x + all->dx*MS)][(int)all->plr.y] == '0')
			all->plr.x += all->dx * MS;
		if (all->map[(int)(all->plr.x)][(int)(all->plr.y +all->dy*MS)] == '0')
			all->plr.y += all->dy * MS;
//		printf("W\n"); this is not the matter
*/
		if (all->map[(int)(all->plr.y)][(int)(all->plr.x + all->dx*MS)] != '1')
			all->plr.x += all->dx * MS;
		if (all->map[(int)(all->plr.y + all->dy*MS)][(int)(all->plr.x)] != '1')
			all->plr.y += all->dy * MS;
//		printf("plr(%f;%f)", all->plr.x, all->plr.y);
	}
	if (key == S)
	{
/*
		if (all->map[(int)(all->plr.x - all->dx*MS)][(int)all->plr.y] == '0')
			all->plr.x -= all->dx * MS;
		if (all->map[(int)(all->plr.x)][(int)(all->plr.y - all->dy*MS)] == '0')
			all->plr.y -= all->dy * MS;
*/
		if (all->map[(int)all->plr.y][(int)(all->plr.x - all->dx*MS)] != '1')
			all->plr.x -= all->dx * MS;
		if (all->map[(int)(all->plr.y - all->dy*MS)][(int)(all->plr.x)] != '1')
			all->plr.y -= all->dy * MS;
//		printf("plr(%f;%f)", all->plr.x, all->plr.y);
	}
	if (key == D)
	{
		double odx = all->dx;
		all->dx = all->dx * cos(-MS) - all->dy * sin(-MS);
		all->dy = odx * sin(-MS) + all->dy * cos(-MS);
		double opx = all->planex;
		all->planex = all->planex * cos(-MS) - all->planey * sin(-MS);
		all->planey = opx * sin(-MS) + all->planey * cos(-MS);
//		printf("planeX=%f, planeY=%f; dirX = %f, dirY = %f\n", all->planex, all->planey, all->dx, all->dy);
    }
	if (key == A)
	{
		double odx = all->dx;
		all->dx = all->dx * cos(MS) - all->dy * sin(MS);
		all->dy = odx * sin(MS) + all->dy * cos(MS);
		double opx = all->planex;
		all->planex = all->planex * cos(MS) - all->planey * sin(MS);
		all->planey = opx * sin(MS) + all->planey * cos(MS);
//		printf("planeX=%f, planeY=%f; dirX = %f, dirY = %f\n", all->planex, all->planey, all->dx, all->dy);
//		printf("key = D;dx=%f, dx=%f, plx=%f, ply=%f\n", all->dx, all->dy, all->planex, all->planey);
	}
	if (key == 65307)//53)
		exit(0);
	if (key == T)
	{
		all->plr.x += 1 * all->dx;
		all->plr.y += 1 * all->dy;
	}
	clear_img2(&all->img, WIDTH, HEIGHT);
//	draw_only_map_scale(all, &point, &all->img);
//	draw_plr_scale(&all->img, all->plr.x, all->plr.y, PLR);
	draw_plr2(&all->img, all);
//	printf("heeeeere\n");
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}
