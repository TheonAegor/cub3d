#include "cub3d.h"

int find_only_plr(t_all *all)
{
	int i;
	int j;
	int max_x;

	i = 0;
	max_x = 0;
    while (all->map[i])     
    {                      
        j = 0;     
        while(all->map[i][j])     
        {                        
			if (j > max_x)
				max_x = j;
            if (all->map[i][j] == 'N')     
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

static int find_range_x(t_point_int *p, int x, int y, int lim)
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
	return (-1);
}

int check_bounds(t_all all)
{
	t_point_int *p;
	int x;
	int y;
	int i;
	int dirx = 1;
	int diry = 0;
	int flag = 0;

	p = malloc(sizeof(t_point_int) * 10000);
	x = -1;
	y = all.map_row;
	printf("%c\n", all.map[8][6]);
	while (flag == 0)
	{
		x++;
		y = 6;
		while ( flag == 0 && all.map[y][x])
		{
			if (all.map[y][x] == '1')
			{
				flag = 1;
				break;
			}
			y++;
		}
	}
	i = 0;
//	sleep(1);
	while (1)
	{
//		printf("%c\n", all.map[y][x]);
//		sleep(1);
		if (all.map[y][x] == '1')
		{
			p[i].x = x;
			p[i].y = y;
			if (p[i].x == p[0].x && p[i].y == p[0].y && i != 0)
			{
				printf("px=%d, py=%d\np[0].x=%d, p[0].y=%d\n", p[i].x, p[i].y, p[0].x, p[0].y);
				break;
			}
			printf("here\n");
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
		printf("x=%d, y=%d, dirx=%d, diry=%d\n", x, y, dirx, diry);
//		sleep(1);
		
	}
	printf("hihihih%d\n", p[93].x);
	printf("%d\n", i);
	if (find_range_x(p, all.plr.x, all.plr.y, i) > 0)
		return (1);
	return (-1);
}
