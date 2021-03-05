#include "cub3d.h"

void	draw_cub(t_data *img, t_p *p, int color)
{
	int xx;
	int yy;

	xx = p->x;
	yy = p->y;
	while (p->y < yy + SCALE)
	{
		my_mlx_pixel_put(img, p->x, p->y, color);		
		p->y++;
	}
	p->y -= SCALE;
	while (p->x < xx + SCALE)
	{
		my_mlx_pixel_put(img, p->x, p->y, color);
		p->x++;	
	}
	p->x -= SCALE;
	p->x += SCALE;
//	p->y += SCALE;
}

int		draw_line_cubes(t_all *all, t_data *img)
{
	t_p p;
	int i;
	int j;

	p.y = START;
	p.x = START;
//	printf("p.y=%f\n", p.y);
//	printf("p.x=%f\n", p.x);
	i = 0;
	j = 0;
	while (all->map[i])
	{
		j = 0;
		p.x = START;
		while(all->map[i][j])
		{
			draw_cub(img, &p, 0x808080);
			j++;
//			p.y++;
		}
		p.y += SCALE;
//		my_mlx_pp_shift(&p.x, &p.y, 1);
	//	printf("y=%d\n", p.y);
		i++;
	}
//	printf("i=%d\n", i);
}

int     draw_only_map_scale(t_all *all, t_point *point, t_data *img)                                          
{         
    int i;
    int j;
          
    i = 0;
    j = 0;             
    point->y = START;
    while (all->map[i])
    {                  
        point->x = START;
//		printf("point->x int draw_only_map=%f\n", point->x);
        j = 0;
        while (all->map[i][j])
        {                                             
            if (all->map[i][j] == '1')                
                my_mlx_pp_scale(img, point, 0xFFFFFF);
            else if (all->map[i][j] == '0')
                my_mlx_pp_scale(img, point, BLACK);
            else if (all->map[i][j] == 'N')
                my_mlx_pp_scale(img, point, BLACK);
            j++;
        }        
		point->y += SCALE;
//        my_mlx_pp_shift(&point->x, &point->y, 1);
        i++;
    }
}

void	new_pp(char **dst, int color)
{
	int i;
	
	i =0;
	while (dst[i])
	{
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
//	printf("point->x int in my_mlx_pp_scale=%f\n", point->x);
	dst = (char **)malloc(sizeof(char *) * (WIDTH * HEIGHT));
	scale_y = (int)point->y + SCALE;
	scale_x = (int)point->x + SCALE;
	while ((int)point->y < scale_y)
	{
		while ((int)point->x < scale_x)
		{
			my_mlx_pixel_put(data, (int)point->x, (int)point->y, color);
			point->x++;
		}
		point->x -= SCALE;
		point->y++;
	}
	point->y -= SCALE;
	point->x += SCALE;
}

//рисуем карту в изображении
int		draw_map_scale(t_all *all, t_point *point, t_data *img)
{
	int i;
	int j;	

	point->y = START;
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
				my_mlx_pp_scale(img, point, BLACK);
			else if (all->map[i][j] == 'N')
			{
				all->plr.x = point->x;
				all->plr.y = point->y;
				all->plr.angle = DIRECTION;
				my_mlx_pp_scale(img, point, BLACK);
			}
			j++;
		}
//				my_mlx_pp_scale(img, point, BLACK);
		point->y += SCALE;
//		my_mlx_pp_shift(&point->x, &point->y, 1);
		i++;
	}
//	printf("plr.x=%f, plr.y=%f\n", all->plr.x, all->plr.y);
//	printf("plr.x=%d, plr.y=%d\n", (int)all->plr.x, (int)all->plr.y);
}

int		show_map(t_all *all)
{
	t_data		img;
	t_point		point;

	all->point.x = 100;
	all->point.y = 100;
	point.x = 100;
	point.y = 100;
//	printf("%d,%d\n", all->plr.x, all->plr.y);	
	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, WIDTH, HEIGHT, "test");
	all->img.img = mlx_new_image(all->vars.mlx, WIDTH, HEIGHT);
	all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.llen, &all->img.en);
//	draw3D(all);
	draw_screen_scale(all, &point, &all->img);
	mlx_hook(all->vars.win, 2, (1L << 0), &key_press, all);
//	mlx_loop(all->game.vars.mlx);
	mlx_loop(all->vars.mlx);
}
