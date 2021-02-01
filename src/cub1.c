#include "cub3d.h"



int		my_mlx_pp_scale(t_data *data, t_point *point, int color, int scale)
{
	char *dst;
	int		scale_y;
	int		scale_x;

	scale_y = point->y + scale;
	scale_x = point->x + scale;
	while (point->y < scale_y)
	{
		while (point->x < scale_x)
		{
			dst = data->addr + (point->y * data->llen + point->x * (data->bpp / 8));
			*(unsigned int*)dst = color;
			point->x++;
		}
		point->x -= scale;
		point->y++;
	}
	point->y -= scale;
	point->x += scale;
}

int		my_mlx_pp_shift(t_point *point, int flag, int scale)
{
	flag == 0 ? (point->x += scale) : (point->y += scale);
	return (1);
}

int		make_map_img(t_all *all, t_point *point, t_data *img)
{
	int i;
	int j;	
	int scale = 30;

	i = 0;
	j = 0;
	while (all->map[i])
	{
		point->x = 100;
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				my_mlx_pp_scale(img, point, 0xFFFFFF, scale);
			else if (all->map[i][j] == '0')
				my_mlx_pp_shift(point, 0, scale);
			else if (all->map[i][j] == 'N')
				my_mlx_pp_scale(img, point, 255, scale);
			j++;
		}
		my_mlx_pp_shift(point, 1, scale);
		i++;
//		printf("here\n");
	}
}

int		show_map(t_all *all)
{
	t_data		img;
	t_point		point;

	point.x = 100;
	point.y = 100;
	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, 640, 480, "test");
	img.img = mlx_new_image(all->vars.mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.en);
	make_map_img(all, &point, &img);
//	my_mlx_pp(&img, point.x, point.y, 0xFFFFFF); 
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, img.img,0, 0);	
	mlx_loop(all->vars.mlx);
}
