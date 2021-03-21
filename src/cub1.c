#include "cub3d.h"
/*
*/
unsigned int    my_mlx_get_color(t_image_e data, int x, int y)
{
        char    *dst;

        dst = data.addr + (y * data.llen + x * (data.bpp / 8));
        return (*(unsigned int *)dst);
}

void			push_img_to_texture(char *path, int num, t_all *all)
{
	int x;
	int y;

	all->image_e.img = mlx_xpm_file_to_image(all->vars.mlx, path, &all->image_e.img_w, &all->image_e.img_h);
//	printf("%p\n", all->image_e.img);
	all->image_e.addr = mlx_get_data_addr(all->image_e.img, &all->image_e.bpp, &all->image_e.llen, &all->image_e.end);
//	printf("gere22\n");
	x = 0;
	while (x < TW)
	{
		y = 0;
		while (y < TH)
		{
			all->texture[num][TW * y +x] = my_mlx_get_color(all->image_e, x, y);
			y++;
		}
		x++;
	}
}


void	find_plr(t_all *all)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	all->w = 0;
	all->h = 0;
	x = 0;
	push_img_to_texture(all->no, 0, all);
	push_img_to_texture(all->sou, 1, all);
	push_img_to_texture(all->we, 2, all);
	push_img_to_texture(all->ea, 3, all);
	push_img_to_texture(all->sp, 4, all);
/*
	all->image_e.filename = (char**)malloc(sizeof(char*)*8);
	while (i < 8)
	{
		all->image_e.filename[i] = malloc(sizeof(char)*100);
		i++;
	}
	(all->image_e).filename[0][0] = 'g';
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
*/
/*
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
	i = all->brd.map_row;
//	printf("map_row%d\n", all->brd.map_row);
//	printf("gotcha\n");
	while (all->map[i])
	{
		j = 0;
		while(all->map[i][j])
		{
			if (ft_strchr("NWES",all->map[i][j]))
			{
				all->sow = all->map[i][j];
				all->plr.x = (double)j;
				all->plr.y = (double)i;
				printf("%f:%f)\n",all->plr.x,all->plr.y);
			}
			if (ft_strchr("NEWS", all->map[i][j]))
				all->map[i][j] = '0'; 
			j++;
		}
		i++;
	}
*/
	if (all->sow == 'N')
	{
		all->dx = 0;
		all->dy = -1;
		all->planex = -0.66;
		all->planey = 0;
	}
	else if (all->sow == 'S')
	{
		all->dx = 0;
		all->dy = 1;
		all->planex = 0.66;
		all->planey = 0;
		
	}
	else if (all->sow == 'E')
	{
		all->dx = 1;
		all->dy = 0;
		all->planex = 0;
		all->planey = -0.66;
	}	
	else if (all->sow == 'W')
	{
		all->dx = -1;
		all->dy = 0;
		all->planex = 0;
		all->planey = 0.66;

	}
	printf("inside find_plr, before count spr\n");
	count_sprites(all);
	create_spr_tabl(all);
/*
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
*/
printf("plr: %f,%f\n", all->plr.x, all->plr.y);
i = 0;
}

void sort_sprites(int *so, double *sd, t_all *all)
{
	int i = 0;	
	int j = 0;
	int tmp_order;
	double tmp_dist;
	t_sprites sprites[all->spr.num_spr];

	while (i < all->spr.num_spr)
	{
		sprites[i].first = sd[i]; 			
		sprites[i].second = so[i];
//		printf("%f::%d\n", sprites[i].first,  sprites[i].second);			
		i++;
	}
	while (j < all->spr.num_spr / 2 + 1)
	{
		i = 0;
  		while (i < all->spr.num_spr - 1)
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
	while (i < all->spr.num_spr)
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
			y++;
		}
		x++;
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


int		show_map(t_all *all)
{
	t_data		img;
	t_point		point;

//	if (parse_map(all) < 0)
//		return (-1);
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
