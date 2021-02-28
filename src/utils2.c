#include "cub3d.h"

float		angle_to_rad(float degree)
{
	return (degree / (180 / PI));
}

void		angle_dist(t_all *all)
{
	printf("angl: %d\n", all->plr.angle);
	if (all->plr.angle >= 90 && all->plr.angle <= 180)
		first_quarter(all);
	if (all->plr.angle >= 0 && all->plr.angle < 90)
		second_quarter(all);
	if (all->plr.angle > 180 && all->plr.angle <= 270)
		third_quarter(all);
	if (all->plr.angle > 270 && all->plr.angle <= 360)
		forth_quarter(all);
}
float		forth_quarter(t_all *all)
{
	float x;
	float y;
	float tang;

	x = 0;
	y = 0;
	tang = roundf((tan(angle_to_rad(all->plr.angle)))* 100) / 100;
/*
	printf("cos = %f\n", cos(angle_to_rad(all->plr.angle)));
	printf("sin = %f\n", sin(angle_to_rad(all->plr.angle)));
	printf("tang = %f\n", tang);
//	printf("tan = %f\n", tang);
*/
	while (x > (MAX_RAY) * cos(angle_to_rad(all->plr.angle)) )
	{
//		printf("inside x\n");
		y = 0;
		while(y < (-MAX_RAY) * sin(angle_to_rad(all->plr.angle))) 
		{
//			printf("inside y\n");
			if (fabs(roundf(y/x * 100) / 100) == fabs(tang))
			{
				my_mlx_pixel_put(&all->img, x + all->plr.x, y + all->plr.y, 0xff0000);
				my_mlx_pixel_put(&all->img, x + all->plr.x + 1, y + 1 + all->plr.y, 0xff0000);
				my_mlx_pixel_put(&all->img, x + all->plr.x - 1, y + all->plr.y - 1, 0xff0000);
				break;
			}
			y = y + 0.1;
		}
		x = x - 0.1;
	}
}
float		third_quarter(t_all *all)
{
	float x;
	float y;
	int ang;
	float tang;

	x = 0;
	y = 0;
	ang = 340;
	tang = roundf((tan(angle_to_rad(all->plr.angle)))* 100) / 100;
/*
	printf("cos = %f\n", cos(angle_to_rad(all->plr.angle)));
	printf("sin = %f\n", sin(angle_to_rad(all->plr.angle)));
	printf("tang = %f\n", tang);
//	printf("tan = %f\n", tang);
*/
	while (x < (MAX_RAY) * cos(angle_to_rad(all->plr.angle)) )
	{
//		printf("inside x\n");
		y = 0;
		while(y < (-MAX_RAY) * sin(angle_to_rad(all->plr.angle))) 
		{
//			printf("inside y\n");
			if (fabs(roundf(y/x * 100) / 100) == fabs(tang))
			{
				my_mlx_pixel_put(&all->img, x + all->plr.x, y + all->plr.y, 0xff0000);
				break;
			}
			y = y + 0.1;
		}
		x = x + 0.1;
	}
}
float		first_quarter(t_all *all)
{
	float x;
	float y;
	float tang;

	x = 0;
	y = 0;
	tang = roundf((tan(angle_to_rad(all->plr.angle)))* 100) / 100;
/*
	printf("cos = %f\n", cos(angle_to_rad(all->plr.angle)));
	printf("sin = %f\n", sin(angle_to_rad(all->plr.angle)));
	printf("tang = %f\n", tang);
	printf("angle = %f\n", all->plr.angle);
	printf("tan = %f\n", tang);
*/
	while (x > (MAX_RAY) * cos(angle_to_rad(all->plr.angle)) )
	{
//		printf("inside x\n");
		y = 0;
		while(y > (-MAX_RAY) * sin(angle_to_rad(all->plr.angle))) 
		{
//			printf("inside y\n");
			if (fabs(roundf(y/x * 10) / 10) == fabs(tang))
			{
				my_mlx_pixel_put(&all->img, x + all->plr.x, y + all->plr.y, 0xff0000);
				break;
			}
			y = y - 0.1;
		}
		x = x - 0.1;
	}
}
float		second_quarter(t_all *all)
{
	float x;
	float y;
	int ang;
	float tang;

	x = 0;
	y = 0;
	ang = 360;
	tang = roundf((tan(angle_to_rad(all->plr.angle)))* 100) / 100;
/*
	printf("cos = %f\n", cos(angle_to_rad(all->plr.angle)));
	printf("sin = %f\n", sin(angle_to_rad(all->plr.angle)));
//	printf("tan = %f\n", tang);
*/
	while (x < (MAX_RAY) * cos(angle_to_rad(all->plr.angle)) )
	{
		y = 0;
		while(y > (-MAX_RAY) * sin(angle_to_rad(all->plr.angle))) 
		{
			if (fabs(roundf(y/x * 100) / 100) == tang)
			{
				my_mlx_pixel_put(&all->img, x + all->plr.x, y + all->plr.y, 0xff0000);
				break;
			}
			y = y - 0.1;
		}
		x = x + 0.1;
	}
}

int		release_ray(t_all *all)
{
	int x;
	int y;
	char *dst;

//	printf("x = %d, y= %d, SCALE = %d, col = %d\n", all->plr.x, all->plr.y, SCALE);
	x = all->plr.x + SCALE/2;
	y = all->plr.y + SCALE/2;
	while(y > 0)
	{
		dst = all->img.addr + (y*all->img.llen + x * all->img.bpp / 8);
//		printf("dst=%u\n", *dst);
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

void	distributor(int key, t_all *all)
{
	t_point point;
	int		time_s;

	point.x = START;
	point.y = START;
//	point.angle = 90;
//	all->plr.angle = point.angle;
//	printf("in dist%d\n", all->plr.angle);
//	printf("img->addr:%i\n", all->img.addr);
	if (key == W)
		all->plr.y--;
	if (key == A)
		all->plr.x--;
	if (key == S)
		all->plr.y++;
	if (key == D)
		all->plr.x++;
	if (key == 65307)
		exit(0);
	time_s = clock();
	clear_img2(&all->img, WIDTH, HEIGHT);
//	printf("time=%d\n", clock()-time_s);
	draw_only_map_scale(all, &point, &all->img);
	angle_dist(all);
//	release_ray(all);
	draw_plr_scale(&all->img, all->plr.x, all->plr.y, PLR);
//	forth_quarter(all);
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
