#include "cub3d.h"

int find_only_plr(t_all *all)
{
	int i;
	int j;
	int flag;

	i = all->brd.map_row;
	flag = 0;
    while (all->map[i])     
    {                      
        j = 0;     
        while(all->map[i][j])     
        {                        
            if (ft_strchr("NSWE", all->map[i][j]))     
            {                             
				all->sow = all->map[i][j];
                all->plr.x = (double)j + 0.5;     
                all->plr.y = (double)i + 0.5;     
				flag += 1;
            }
            if (ft_strchr("NSWE", all->map[i][j]))     
				all->map[i][j] = '0';
            j++;                              
        }
        i++;     
    } 
	if (flag != 1)
	{
		handle_plr_errors(flag);
		return (-1);
	}
	return (1);
}

static int check_neighbors(t_all *all, int y, int x)
{
	if (all->map[y + 1])
	{
		if (all->map[y + 1][x] == ' ' || x - 1 < 0 || ft_strchr(" \0", all->map[y + 1][x + 1]) || ft_strchr(" \0", all->map[y + 1][x - 1]))	
			return (-1);
	}
	else
		return (-1);
	if (all->map[y - 1])
	{
		if (all->map[y - 1][x] == ' ' || x - 1 < 0 || ft_strchr(" \0", all->map[y - 1][x + 1]) || ft_strchr(" \0", all->map[y - 1][x - 1]) )	
			return (-1);
	}
	else
		return (-1);
	return (1);
}

int check_bounds2(t_all *all, t_brd *brd)
{
	int y;
	int x;
	int res;

	y = brd->map_row;
	x = 0;
	res = 0;
	while (all->map[y])
	{
		x = 0;
		while (all->map[y][x])
		{
			if (ft_strchr("NSWE02", all->map[y][x]))
			{
				res = check_neighbors(all, y, x);	
				if (res < 0)
				{
					handle_map_errors(x, y);
					return (res);
				}
			}
			x++;
		}
		y++;
	}
	return (res);
}
