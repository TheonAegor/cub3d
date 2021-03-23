#include "cub3d.h"

void		my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
//	printf("dst=%u\n", dst);
//	printf("img.addr%i\n", img->addr);
	*(unsigned int*)dst = color;
}

void		pix_put_plr(t_data *img, float x, float y, int color)
{
	char *dst;
	int xx;
	int yy;

	xx = (int)floor(x);
	yy = (int)floor(y);
	dst = img->addr + (yy * img->llen + xx * (img->bpp / 8));
//	printf("dst=%u\n", dst);
//	printf("img.addr%i\n", img->addr);
	*(unsigned int*)dst = color;
}

int draw_screen_scale(t_all *all, t_point *point, t_data *img)
{
	find_plr(all);
	middle_init(all);
//	printf("here\n");
	draw_plr2(img, all);
	if (all->save == 1)
	{
		printf("here\n");
		screen_shot(all);
		free_all(all);
		return (-1);
	}
	mlx_do_sync(all->vars.mlx);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
}


int		parse_map(t_all *all)
{
	int err;
	int i;
	int full;

	err = 1;
	i = -1;
	full =0;
	start_init(all);
	/*			parse RESOLUTION		*/
	while (all->map[++i])
	{
		if (all->map[i][0] == 'R') 
			err = parse_r(all->map[i], &all->w, &all->h, &full);
		if (all->map[i][0] == 'N' &&  all->map[i][1] == 'O')
			err = parse_side(all->map[i], &all->no, &full, 0);
		if (all->map[i][0] == 'S' &&  all->map[i][1] == 'O')
			err = parse_side(all->map[i], &all->sou, &full, 0);
		if (all->map[i][0] == 'W' &&  all->map[i][1] == 'E')
			err = parse_side(all->map[i], &all->we, &full, 0);
		if (all->map[i][0] == 'E' &&  all->map[i][1] == 'A')
			err = parse_side(all->map[i], &all->ea, &full, 0);
		if (all->map[i][0] == 'S' && all->map[i][1] != 'O')
			err = parse_side(all->map[i], &all->sp, &full, 0);
		if (all->map[i][0] == 'F')
			err = parse_side(all->map[i], &all->floor_c, &full,1);
		if (all->map[i][0] == 'C')
			err = parse_side(all->map[i], &all->ceil_c, &full, 1);
		if (err != 1)
		{
			handle_parse_err(err, all);
			return (-1);
		}
		if (full == 8)
		{
			all->brd.map_row = i + 1;
			full++;
		}
	}
//	printf("fulfilment = %d\n", full);	
	if (full != 9)
	{
		handle_parse_err(full + 700, all);
		return (-1);
	}
	if (check_hex(all) == -1)
		return (-1);
	all->color.floor = to_hex(all->floor_c);
	all->color.ceil = to_hex(all->ceil_c);
	if (all->color.floor == 1 || all->color.ceil == 1)
	{
//		ft_printf("ololol\n");
		handle_hex_err(-1, all);
		return (-1);
	}
	printf("w=%d, h=%d, %s, %s, %s, %s, %s, %s, %s\n",all->w, all->h, all->no, all->sou, all->we, all->ea, all->sp, all->floor_c, all->ceil_c);
	return (err);
}

int		parse_r(char *res, int *w, int *h, int *full)
{
	int i;	
	
	i = 1;	
	*w = ft_atoi(&res[i]);
	while(res[i] == ' ')
		i++;
	while(ft_isdigit(res[i]))
		i++;
	*h = ft_atoi(&res[i]);
	if (*w <= 0 || *h <= 0)
		return (-23);
//	printf("w=%d,h=%d\n", *w, *h);
	if (*w > 2048)
		*w = 2048;	   
	if (*h > 1024)
		*h = 1024;
//	printf("w=%d,h=%d\n", *w, *h);
	*full += 1;
	return (1);
}

int parse_side(char *path, char **side, int *full, int flag)
{
	int i;
	int err;

	i = 2;
	err = 1;
//	printf("map[i]=%s\n", path);
	while (path[i] == ' ')
		i++;
	if (flag == 0)
	{
		err = open(&path[i], O_RDONLY);
//		printf("%s\n", &path[i]);
		if (err < 0)
			return (path[0] + path[1]);
		close(err);
	}
	else
		i = 1;
	*side = &path[i];
	*full += 1;
//	printf("%s\n", &path_no[i]);
	return (1);
}

void	draw_plr2(t_data *img, t_all *all)
{
	t_dda	dda;
	t_spr_cast	s;

	dda.x = 0;
	while (dda.x < all->w)
	{
		start_dda(&dda, all);
		find_side(&dda, all);
		find_hit(&dda, all);
		find_start_end(&dda, all);
		determine_num_texture(&dda, all);
		wall_and_text(&dda, all);
		fill_buf(&dda, all);
	}
	precasting(&s, all);	
	s.i = 0;
	while (s.i < all->spr.num_spr)
	{
		spr_cast1(&s, all);	
		spr_cast2(&s, all);	
		s.i++;
	}
	draw_buffer(&all->img, all);
	clear_buffer(all);
}

int		key_press(int key, t_all *all)
{
	printf("%d\n", key);
	distributor(key, all);
	return (key);
}
