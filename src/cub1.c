#include "cub3d.h"

static int scale = 50;

int		scale_map(t_vars *vars, t_point *point, int pass, int col)
{
	int	scale_y;
	int scale_x;
//	int scale;

//	scale = 10
	scale_y = scale + point->y;
	scale_x = scale + point->x;
	if (pass == 0)
	{
		while (point->y < scale_y)
		{
			point->x = scale_x - scale;
			while(point->x < scale_x) 
			{
				mlx_pixel_put(vars->mlx, vars->win,
						point->x++, point->y, col);
			}
			point->y++;
		}
		point->y = scale_y - scale;
	}
	else
		point->x += scale;
	return (1);
}

int		show_map(char **map)
{
	int		i;
	int		j;
	t_point	point;
	t_vars	vars;
	
	i = 0;
	j = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello");
	point.y = 100;
	while (map[i])
	{
		j = 0;
		point.x = 100;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				scale_map(&vars, &point, 0, 0xFFFFFF);
			else if (map[i][j] == 'N')
				scale_map(&vars, &point, 0, 100);
			else
				scale_map(&vars, &point, 1, 0);
			j++;
		}
		point.y += scale;
		i++;
	}
	mlx_loop(vars.mlx);
}
