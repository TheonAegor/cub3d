#include "header.h"
#include <mlx.h>

int main(void)
{
	void *mlx;
	void *mlx_win;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 100, 100, "hello world!");
	mlx_loop(mlx);
/*
	const size_t win_w = 10;	
	const size_t win_h = 10;	
	int i;
	int j;

	
	i = 0;
	start_color(4);
	while (i++ < win_h)
	{
		j = 0;
		while (j++ < win_w)
			printf(".");
		printf("\n");
	}
*/

	return (1);
}
