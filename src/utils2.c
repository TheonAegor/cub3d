#include "cub3d.h"

int		release_ray(t_all *all)
{
	int x;
	int y;
	char *dst;

	x = all->plr.x + SCALE/2;
	y = all->plr.y + SCALE/2;
	while(y > 0)
	{
		dst = all->img.addr + (y*all->img.llen + x * all->img.bpp / 8);
		printf("dst=%u\n", *dst);
		if (*(unsigned int *)dst == WALL)
			return (1);
		my_mlx_pixel_put(&all->img, x, y, 0xff0000);
		y--;
	}
}

int		draw_only_map_scale(t_all *all, t_point *point, t_data *img)
{
	int i;
	int j;	

	i = 0;
	j = 0;
	while (all->map[i])
	{
		point->x = 100;
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				my_mlx_pp_scale(img, point, 0xFFFFFF);
			else if (all->map[i][j] == '0')
				my_mlx_pp_shift(point, 0);
			else if (all->map[i][j] == 'N')
				my_mlx_pp_shift(point, 0);
			j++;
		}
		my_mlx_pp_shift(point, 1);
		i++;
	}
}

void	go_up(t_data *img, t_all *all)
{
//	printf("in dist\n");
//	printf("img->addr:%i\n", all->img.addr);
	draw_plr_scale(img, all->plr.x, all->plr.y, BLACK);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
	all->plr.y++;
	draw_plr_scale(img, all->plr.x, all->plr.y, PLR);
}

void	distributor(int key, t_all *all)
{
	t_point point;
	int		time_s;

	point.x = START;
	point.y = START;
//	printf("img->addr:%i\n", all->img.addr);
	if (key == W)
		all->plr.y--;
	else if (key == A)
		all->plr.x--;
	else if (key == S)
		all->plr.y++;
	else if (key == D)
		all->plr.x++;
	time_s = clock();
	clear_img2(&all->img, WIDTH, HEIGHT);
	printf("time=%d\n", clock()-time_s);
	draw_only_map_scale(all, &point, &all->img);
	release_ray(all);
	draw_plr_scale(&all->img, all->plr.x, all->plr.y, PLR);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}

void	clear_img2(t_data *img, int w, int h)
{
	int x;
	int y;

	x = 0;
	while (x <= w )
	{
		y = 0;
		while (y <= h)
		{
			my_mlx_pixel_put(img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}
