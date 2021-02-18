#include "cub3d.h"

int		close_win(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
}

int		key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65362)
	{
		;
	}
	printf("keycode is %d\n", keycode);
}

int		mouse_hook(int button, int x, int y, t_vars *vars)
{
	printf("(x,y):(%d,%d);button = %d\n", x, y, button);
}
