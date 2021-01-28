#include "header.h"
#include <mlx.h>
#include <math.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

int sqrt2(int x)
{
	return (x / x);
}

int hyp(int x, int y)
{
	return (sqrt(x*x + y*y));
}

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int dim = 50;
	int center = 200;
	int x = center - dim;
	int y = center - dim;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "test");
	while (y++ <= center + dim)
	{
		x = center-dim;
		while(x++ <= center + dim)
		{
			if (pow((x - center), 2) + pow((y - center),2) <= pow(dim,2))
				mlx_pixel_put(mlx, mlx_win, x, y, 0xffffff);
		}
	}
	int side = 50;
	x = 50;
	y = 0;
	while (y++ <= 25)
	{
		x = 0;
		while (x++ <= limit)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, 0xffffff);
		}	
		limit -= 50 / 25;
	}
	mlx_loop(mlx);
	return (1);
}
