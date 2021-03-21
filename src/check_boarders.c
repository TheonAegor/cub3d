#include "cub3d.h"

static void find_max_x(t_point_int *p, int lim, t_brd *brd)
{
	int i;
	
	i = 0;
	brd->max = 0;
	while (i < lim)
	{
		if (p[i].x > brd->max)
			brd->max = p[i].x;
		i++;
	}
}

int find_only_plr(t_all *all)
{
	int i;
	int j;
	int max_x;

	i = 0;
	max_x = 0;
	all->plr.x = -1;
	all->plr.y = -1;
    while (all->map[i])     
    {                      
        j = 0;     
        while(all->map[i][j])     
        {                        
			if (j > max_x)
				max_x = j;
            if (ft_strchr("NSWE", all->map[i][j]))     
            {                             
                all->plr.x = (double)j;     
                all->plr.y = (double)i;     
            }                                                
            j++;                              
        }           
        i++;     
    } 
	if (all->plr.x == 0 && all->plr.y == 0)
		return (-1);
	all->plr.max_x = max_x;
	return (1);
}

static int check_plr(int x, int min, int max)
{
	if (x > min && x < max)
		return (1);
	return (-1);
}

static int find_range_y(t_point_int *p, int x, int y, int lim, t_brd *brd)
{
	int i;
	int max;
	int min;
	
	i = 0;
	min = 10000;
	max = 0;
	while (i < lim)
	{
		if (p[i].x == x)
		{
			if (p[i].y < min)
				min = p[i].y;	
			if (p[i].y > max)
				max = p[i].y;
		}
		i++;
	}
	if (min < 10000)
		if (check_plr(y, min, max) > 0)
		{
			printf("max=%d, min=%d\n", max, min);
			return(1);
		}
	printf("min_y=%d, max_y = %d\n", min, max);
	return (-1);
}

static int find_range_x(t_point_int *p, int x, int y, int lim, t_brd *brd)
{
	int i;
	int max;
	int min;
	
	i = 0;
	min = 10000;
	max = 0;
	while (i < lim)
	{
		if (p[i].y == y)
		{
			if (p[i].x < min)
				min = p[i].x;	
			if (p[i].x > max)
				max = p[i].x;
		}
		i++;
	}
	if (min < 10000)
		if (check_plr(x, min, max) > 0)
		{
			printf("max=%d, min=%d\n", max, min);
			return(1);
		}
	printf("min_x=%d, max_x = %d\n", min, max);
	return (-1);
}

int check_bounds(t_all all, t_brd *brd, int start_x)
{
	t_point_int *p;
	int y;
	int x;
	int i;
	int dirx = 1;
	int diry = 0;
	int flag = 0;
	int	hole = 0;

	p = malloc(sizeof(t_point_int) * 10000);
//	printf("%c\n", all.map[8][6]);
	printf ("y = %d\n", y = brd->map_row);
	y = brd->map_row - 1;
	while (flag == 0)
	{
		y++;
		x = start_x;
		while ( flag == 0 && all.map[y][x])
		{
			if (all.map[y][x] == '1')
			{
				flag = 1;
				brd->map_row = y;
				break;
			}
			x++;
		}
	}
	i = 0;
//	sleep(1);
	while (1)
	{
//		printf("%c\n", all.map[y][x]);
//		sleep(1);
		if ((p[i].x == p[0].x && p[i].y == p[i].y) && (p[i].dirx != p[0].dirx || p[i].diry != p[0].diry) && i != 0)
		{
			hole = 1;
			break;
		}
		if (x >= 0 && all.map[y][x] == '1')
		{
			p[i].x = x;
			p[i].y = y;
			p[i].dirx = dirx;
			p[i].diry = diry;
		if ((p[i].x == p[0].x && p[i].y == p[i].y) && (p[i].dirx == p[0].dirx && p[i].diry == p[0].diry) && i != 0)
			{
//				printf("px=%d, py=%d\np[0].x=%d, p[0].y=%d\n", p[i].x, p[i].y, p[0].x, p[0].y);
				break;
			}
//			printf("here\n");
			if (dirx == 1)
			{
				dirx -= 1;
				diry -= 1;
			}
			else if (dirx == -1)
			{
				dirx += 1;
				diry += 1;
			}
			else if (diry == -1)
			{
				dirx -= 1;
				diry += 1;
			}
			else
			{
				dirx += 1;
				diry -= 1;
			}
			y += diry;
			x += dirx;
			i++;
		}
		else
		{
			if (dirx == 1)
			{
				dirx -= 1;
				diry += 1;
			}
			else if (dirx == -1)
			{
				dirx += 1;
				diry -= 1;
			}
			else if (diry == -1)
			{
				dirx += 1;
				diry += 1;
			}
			else
			{
				dirx -= 1;
				diry -= 1;
			}
			y += diry;
			x += dirx;
		}
//		printf("x=%d, y=%d, dirx=%d, diry=%d\n", x, y, dirx, diry);
//		sleep(1);
		
	}
//	printf("hihihih%d\n", p[93].x);
	printf("hole=%d\n", hole);
	if (find_range_x(p, all.plr.x, all.plr.y, i, brd) > 0)
		return (1);
	find_max_x(p, i, brd);
	return (-1);
}
