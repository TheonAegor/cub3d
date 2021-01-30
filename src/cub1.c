#include "cub3d.h"

int		my_mlx_pp(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
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
	my_mlx_pp(&img, point.x, point.y, 0xFFFFFF); 
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, img.img,0, 0);	
	mlx_loop(all->vars.mlx);
	
}
