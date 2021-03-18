#include "cub3d.h"
/*
*/
unsigned int    my_mlx_get_color(t_image_e data, int x, int y)
{
        char    *dst;

        dst = data.addr + (y * data.llen + x * (data.bpp / 8));
        return (*(unsigned int *)dst);
}

void	find_plr(t_all *all)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
    all->dx = -1;
   	all->dy = 0;
	all->planex = 0;	
    all->planey = 0.66;
	all->w = 0;
	all->h = 0;
	x = 0;
/*
	all->image_e.filename = (char**)malloc(sizeof(char*)*8);
	while (i < 8)
	{
		all->image_e.filename[i] = malloc(sizeof(char)*100);
		i++;
	}
	(all->image_e).filename[0][0] = 'g';
*/
	all->image_e.filename[0] = "pics/eagle.xpm";
	all->image_e.filename[1] = "pics/wall_1.xpm";
	all->image_e.filename[2] = "pics/bluestone.xpm";
	all->image_e.filename[3] = "pics/wall_2.xpm";
	all->image_e.filename[4] = "pics/wall_3.xpm";
	all->image_e.filename[5] = "pics/wall_4.xpm";
	all->image_e.filename[6] = "pics/wood.xpm";
	all->image_e.filename[7] = "pics/greystone.xpm";
	all->image_e.filename[8] = "pics/purplestone.xpm";
	all->image_e.filename[9] = "pics/redbrick.xpm";
	all->image_e.filename[10] = "pics/sprite_2.xpm";
	all->image_e.filename[11] = "pics/sprite_1.xpm";
	all->image_e.filename[12] = "pics/pillar.xpm";
	i = 0;
	while (i < 13)
	{
//		printf("%p\n", all->vars.mlx);
//		printf("filename:%p\n", all->image_e.filename[i]);
//		printf("%p\n", mlx_xpm_file_to_image(all->vars.mlx, "./eagle.png", &all->image_e.img_w, &all->image_e.img_h));
		all->image_e.img = mlx_xpm_file_to_image(all->vars.mlx, all->image_e.filename[i], &all->image_e.img_w, &all->image_e.img_h);
//		printf("%p\n", all->image_e.img);
		all->image_e.addr = mlx_get_data_addr(all->image_e.img, &all->image_e.bpp, &all->image_e.llen, &all->image_e.end);
//		printf("gere22\n");
		x = 0;
		while (x < TW)
		{
			y = 0;
			while (y < TH)
			{
				all->texture[i][TW * y +x] = my_mlx_get_color(all->image_e, x, y);
				y++;
			}
			x++;
		}
		i++;
	}
	i = 0;
//	printf("gotcha\n");
	while (all->map[i])
	{
		j = 0;
		while(all->map[i][j])
		{
			if (all->map[i][j] == 'N')
			{
				all->plr.x = (double)j;
				all->plr.y = (double)i;
				printf("%f:%f)\n",all->plr.x,all->plr.y);
			}
/*			if (all->map[i][j] < '0' || all->map[i][j] > '9')
				all->map[i][j] = '0'; */
			j++;
		}
		i++;
	}
t_sprite sprite[NS] = 
{
  {3.5, 7.5, 10}, //green light in front of playerstart
  //green lights in every room
  {3.5,18.5, 10},
  {1.5,4.5, 12},
  {3.5,4.5, 12},
  {3.5,1.5,  12},
  {1.5,1.5,  12},
  {6.5,12.5,  12},
  {6.5,15.5, 12},

  //row of pillars in front of wall: fisheye test
  {14, 3, 12},
  {15, 3, 12},
  {12.5, 2.5, 12},

  //some barrels around the map
  {2.5, 1.5, 10},
  {2.5, 4.5, 10},
  {1.5, 7.5, 10},
  {1.5, 9.5, 10},
  {1.5, 16.5, 10},
  {1.5, 17.5, 10},
  {1.5, 11.5,10},
  {3, 15.8,10},
};
i = 0;
while (i < NS)
{
	all->sprite[i] = sprite[i];
	i++;
}
printf("plr: %f,%f\n", all->plr.x, all->plr.y);
i = 0;
}

void sort_sprites(int *so, double *sd, t_all *all)
{
	int i = 0;	
	int j = 0;
	int tmp_order;
	double tmp_dist;
	t_sprites sprites[NS];

	while (i < NS)
	{
		sprites[i].first = sd[i]; 			
		sprites[i].second = so[i];
//		printf("%f::%d\n", sprites[i].first,  sprites[i].second);			
		i++;
	}
	while (j < NS / 2 + 1)
	{
		i = 0;
  		while (i < NS - 1)
  		{
  			if (sprites[i].first < sprites[i + 1].first)
  			{
//				printf("i:%f\ti+1:%f\n", sprites[i].first, sprites[i + 1].first);
				tmp_dist = sprites[i].first;
				tmp_order = sprites[i].second;
  				sprites[i].first = sprites[i + 1].first;
  				sprites[i].second = sprites[i + 1].second;
				sprites[i + 1].first = tmp_dist;
				sprites[i + 1].second = tmp_order;
  			}
  			i++;
  		}
		j++;
	}
	i = 0;
	while (i < NS)
	{
		all->sd[i] = sprites[i].first;
		all->so[i] = sprites[i].second;
		i++;
	}
//	printf("sd[l:%f,%d],sd[mid[f:%f,%d], sd[f:%f, %d]\n", all->sd[18],all->so[18], all->sd[9],all->so[9], all->sd[0],all->so[0]);
	/*
*/
}	

void draw_buffer(t_data *img, t_all *all)
{
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(img, x, y, all->buffer[y][x]);
//			printf("x=%u, y = %u\n", x, y);
//			printf("buf:%u\n", all->buffer[y][x]);
			y++;
		}
		x++;
	}
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

	if (parse_map(all) < 0)
		return (-1);
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
	if(!(draw_screen_scale(all, &point, &all->img)))
		return (-1);
	mlx_hook(all->vars.win, 2, (1L << 0), &key_press, all);
//	mlx_loop(all->game.vars.mlx);
	mlx_loop(all->vars.mlx);
}
