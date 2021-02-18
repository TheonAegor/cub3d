#include "cub3d.h"
#define DB printf("here\n");
int		my_mlx_pp_scale(t_data *data, t_point *point, int color, int scale)
{
	char	*dst;
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

//рисуем карту в изображении
int		draw_map_scale(t_all *all, t_point *point, t_data *img)
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
			{
				all->plr.x = point->x;
				all->plr.y = point->y;
				my_mlx_pp_shift(point, 0, scale);
//				my_mlx_pp_scale(img, point, 255, scale);
			}
			j++;
		}
		my_mlx_pp_shift(point, 1, scale);
		i++;
//		printf("here\n");
	}
	printf("heren2\n");
//	draw_plr_scale(img, all->plr.x, all->plr.y, 30);
}

int		show_map(t_all *all)
{
	t_data		img;
	t_point		point;

	all->point.x = 100;
	printf("hereee\n");
	all->point.y = 100;
	point.x = 100;
	point.y = 100;
	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, 640, 480, "test");
	all->img.img = mlx_new_image(all->vars.mlx, 640, 480);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.llen, &all->img.en);
	draw_screen_scale(all, &point, &all->img);
//	draw_map_scale(all, &point, &all->img);
//	my_mlx_pp(&img, point.x, point.y, 0xFFFFFF); 
//	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);	
//	mlx_key_hook(all->vars.win, key_hook, &all->vars);
/*
	clear_img(&all->img, 640, 480);
    mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0); 
*/
//	clear_win(&all, 640, 480);
//	mlx_hook(all->vars.win, 2, (1L << 0), &key_press, &all);
	mlx_loop(all->vars.mlx);
}
