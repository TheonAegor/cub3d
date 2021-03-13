#include "cub3d.h"

int main()
{
	t_vars vars;
	t_data img;
	t_image png;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "test");
	png.img = mlx_xpm_file_to_image(vars.mlx, "./eagle.xpm", &png.img_width,&png.img_height);
	printf("%p\n", png.img);
//	png.addr = mlx_get_data_addr(png.img, &png.bpp, &png.line_len, &png.end);
	mlx_loop(vars.mlx);
}
