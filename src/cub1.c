#include "cub3d.h"
#define DB printf("here\n");
void	new_pp(char **dst, int color)
{
	int i;
	
	i =0;
	while (dst[i])
	{
//		printf("dst=%u", **dst);
		*(unsigned int*)(dst[i]) = color;
		i++;
	}
}

int		my_mlx_pp_scale(t_data *data, t_point *point, int color)
{
	char	**dst;
	int		scale_y;
	int		scale_x;
	int		i;

	i = 0;
	dst = (char **)malloc(sizeof(char *) * (WIDTH * HEIGHT));
	scale_y = point->y + SCALE;
	scale_x = point->x + SCALE;
	while (point->y < scale_y)
	{
		while (point->x < scale_x)
		{
			dst[i] = data->addr + (point->y * data->llen + point->x * (data->bpp / 8));
			i++;
//			*(unsigned int*)dst = color;
			point->x++;
		}
		point->x -= SCALE;
		point->y++;
	}
	point->y -= SCALE;
	point->x += SCALE;
	dst[i] = NULL;
	new_pp(dst, color);
}

int		my_mlx_pp_shift(t_point *point, int flag)
{
	flag == 0 ? (point->x += SCALE) : (point->y += SCALE);
	return (1);
}

//рисуем карту в изображении
int		draw_map_scale(t_all *all, t_point *point, t_data *img)
{
	int i;
	int j;	

	i = 0;
	j = 0;
	while (all->map[i])
	{
		point->x = START;
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				my_mlx_pp_scale(img, point, 0xFFFFFF);
			else if (all->map[i][j] == '0')
				my_mlx_pp_shift(point, 0);
			else if (all->map[i][j] == 'N')
			{
				all->plr.x = point->x;
				all->plr.y = point->y;
				my_mlx_pp_shift(point, 0);
//				my_mlx_pp_scale(img, point, 255, SCALE);
			}
			j++;
		}
		my_mlx_pp_shift(point, 1);
		i++;
//		printf("here\n");
	}
//	printf("heren2\n");
//	printf("x = %d, y= %d, SCALE = %d, col = %d\n", all->plr.x, all->plr.y, SCALE);
//	draw_plr_scale(img, all->plr.x, all->plr.y, 30);
}

int		show_map(t_all *all)
{
	t_data		img;
	t_point		point;

	all->point.x = 100;
//	printf("hereee\n");
	all->point.y = 100;
//	all->plr.angle = 90;
	point.x = 100;
	point.y = 100;
	printf("%d,%d\n", all->plr.x, all->plr.y);	
	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, WIDTH, HEIGHT, "test");
	all->img.img = mlx_new_image(all->vars.mlx, WIDTH, HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.llen, &all->img.en);

	draw_screen_scale(all, &point, &all->img);
//	clear_win(&all, 200, 200);
	mlx_hook(all->vars.win, 2, (1L << 0), &key_press, all);
//	clear_img2(&all->img, WIDTH, HEIGHT);
//	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
	mlx_loop(all->vars.mlx);
}
