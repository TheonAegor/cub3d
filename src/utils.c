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
//	printf("here\n");
	draw_plr2(img, all);
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
	all->color.floor = to_hex(all->floor_c);
	all->color.ceil = to_hex(all->ceil_c);
	if (all->color.floor == 1 || all->color.ceil == 1)
	{
		ft_printf("ololol\n");
		handle_hex_err(-1, all);
		return (-1);
	}
//	printf("w=%d, h=%d, %s, %s, %s, %s, %s, %s, %s\n",all->w, all->h, all->no, all->sou, all->we, all->ea, all->sp, all->floor_c, all->ceil_c);
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
	*side = &path[i];
	*full += 1;
//	printf("%s\n", &path_no[i]);
	return (1);
}

void	draw_plr2(t_data *img, t_all *all)
{
	int mx, my, x;
	int i;
	int y;

	i = 0;
		x = 0;
		y = 0;
		while (x < WIDTH)
		{
//			printf("start:dx=%f, dy = %f\n", all->dx, all->dy);
			double camerax = 2 * x/(double)WIDTH - 1;/**/
			double rdx = all->dx + all->planex * camerax; /*Ray dir x*/
			double rdy = all->dy + all->planey * camerax;
//			printf("rdy=%f, rdx = %f\n", rdy, rdx);
			mx = (int)floor(all->plr.x);
			my = (int)floor(all->plr.y);

			double sdy;
			double sdx; //side dist y

			double ddx = (rdy == 0) ? 0 : ((rdx == 0) ? 1 : fabs(1 / rdx));
			double ddy = (rdx == 0) ? 0 : ((rdy == 0) ? 1 : fabs(1 / rdy)); //delta dist y
/*
*/
			double pwd;

			int sx; //step x
			int sy;

			int hit = 0;
			int side; // if x side was hit = 0
			if (rdx < 0)
			{
				sx = -1;
				sdx = (all->plr.x - mx) * ddx;
			}
			else
			{
				sx = 1;
				sdx = (mx + 1.0 - all->plr.x) * ddx;
			}
			if (rdy < 0)
			{
				sy = -1;
				sdy = (all->plr.y - my) * ddy;
			}	
			else 
			{
				sy = 1;
				sdy = (my + 1.0 - all->plr.y) * ddy;
			}
/*
			printf("dx=%f, dy = %f\n", all->dx, all->dy);
			printf("rdx=%f, rdy = %f\n", rdx, rdy);
			printf("ddx= %f, ddy=%f\n", ddx, ddy);
			printf("sdx=%f, sdy = %f\n", sdx, sdy);
			printf("mx= %d, my =%d\n", mx, my);
			printf("x=%d\n", x);
*/
			while ( hit == 0)
			{
				if(sdx < sdy)
				{
					sdx += ddx;
					mx += sx;
					side = 0;
//					printf("here1\n");
				}
				else 
				{
					sdy += ddy;
					my += sy;
					side = 1;
//					printf("here2\n");
				}
/*
				if (my < 0)
					my = 0;
				if (mx < 0)
					mx = 0;
*/
				if (all->map[my][mx] == '1')
				{
					hit = 1;
//					printf("here3\n");
				}
//				printf("inside hit\n");
			}
			if (side == 0)
		/*-------y distance------*/
				pwd = (mx - all->plr.x + (1 - sx)/ 2) / rdx;
			else 
				pwd = (my - all->plr.y + (1 - sy) / 2)/ rdy;

			int lh = (int)(HEIGHT / pwd);
			int ds = -lh / 2 + HEIGHT /2; //draw start
			if (ds < 0)
				ds = 0;
			int de = lh / 2 + HEIGHT / 2; //draw end
			if (de >= HEIGHT)
				de = HEIGHT - 1;
/*
			printf ("ds = %d\n", ds);
			printf("ds=%d, de = %d\n", ds, de);
			printf("dx=%f, dx=%f, plx=%f, ply=%f\n", all->dx, all->dy, all->planex, all->planey);
			int color = 0xff0000;
			if (side == 1)
				color = 0x660000;
			draw_lines(img, ds, de, x, color);
*/
			int tn = all->map[my][mx] - 48 - 1;
			if (rdy > 0)
			{
				tn = 0; 
				if (rdx > 0)
				{
					if (side == 0)
						tn = 2;
				}
				else
				{
					if (side == 0)
						tn = 3;
				}
			}
			else
			{
				tn = 1;
				if (rdx > 0)
				{
					if (side == 0)
						tn = 2;
				}
				else
				{
					if (side == 0)
						tn = 3;
				}
			}
	//		printf("tn=%d\n", tn);

			double wallX;
			if (side == 0)
				wallX = all->plr.y + pwd * rdy;
			else
				wallX = all->plr.x + pwd * rdx;
			wallX -= floor((wallX));

			int texX = (int)(wallX * (double)(TW));
			if(side == 0 && rdx > 0) 
				texX = TW - texX - 1;
			if(side == 1 && rdy < 0) 
				texX = TW - texX - 1;	
			double step = 1.0 * TH/lh;
			double texPos = (ds - HEIGHT/2 + lh /2) * step;
			/*
			y = 1;
			while (y < ds)
			{
				unsigned color = 0x00ff00;
				all->buffer[y][x] = color;
				y++;
			}
			*/
/*
			printf("mx= %d, my =%d\n", mx, my);
			printf("dx=%f, dy = %f\n", all->dx, all->dy);
			printf("rdx=%f, rdy = %f\n", rdx, rdy);
			printf("ddx= %f, ddy=%f\n", ddx, ddy);
			printf("mx= %d, my =%d\n", mx, my);
			printf("outside\n");
*/
			y = 0;
			while (y < ds && ds < de)
			{
				all->buffer[y][x] = all->color.floor;
				y++;
			}
			y = ds;
			while ( y < de)
			{
				int texY = (int)texPos & (TH - 1);
				texPos += step;
				unsigned color = all->texture[tn][TH * texY + texX];
				if (side == 1) 
					color = (color >> 1) & 8355711;
				all->buffer[y][x] = color;
				y++;
			}
			while (y < HEIGHT)
			{
				all->buffer[y][x] = all->color.ceil;
				y++;
			}
			all->zbuf[x] = pwd;
			x += 1;
		}
/*----------------------SPRITE casting-----------------------
 *---*/
		printf("plr(%f:%f)\nsd(%f,%d)\n", all->plr.x, all->plr.y, all->sd[i], all->so[i]);
		i = 0;
		while (i < all->spr.num_spr)
		{
			all->so[i] = i;
			all->sd[i] = ((all->plr.x - all->sprite[i].x) * (all->plr.x - all->sprite[i].x) + (all->plr.y - all->sprite[i].y) * (all->plr.y - all->sprite[i].y));
//			printf("plr(%f:%f)\nsd(%f,%d)\n", all->plr.x, all->plr.y, all->sd[i], all->so[i]);
			i++;
		}
		sort_sprites(all->so, all->sd, all);
//		printf("after_sort\n");
		i = 0;
		while (i < all->spr.num_spr)
		{
			double sprite_x = all->sprite[all->so[i]].x - all->plr.x;
			double sprite_y = all->sprite[all->so[i]].y - all->plr.y;
			double inv_det = 1.0 / (all->planex * all->dy - all->dx * all->planey);
			double transform_x = inv_det * (all->dy * sprite_x - all->dx * sprite_y);
			double transform_y = inv_det * (-all->planey * sprite_x + all->planex * sprite_y);
			int sprite_screen_x = (int)((WIDTH/2)*(1 + transform_x / transform_y));
			int vmove_screen = (int)(VMV / transform_y);
			int spr_h = abs((int)(HEIGHT / transform_y)) / VDIV;
			int drawsy = -spr_h / 2 + HEIGHT / 2 + vmove_screen;
			if (drawsy < 0)
				drawsy = 0;
			int drawey = spr_h / 2 + HEIGHT / 2 + vmove_screen;
			if (drawey >= HEIGHT)
				drawey = HEIGHT - 1;
			int spr_w = abs((int)(HEIGHT / (transform_y))) / UDIV;
			int drawsx = -spr_w / 2 + sprite_screen_x;
			if (drawsx < 0) 
				drawsx = 0;
			int drawex = spr_w / 2 + sprite_screen_x;
			if (drawex >= WIDTH)
				drawex = WIDTH - 1;
			int stripe = drawsx;
//			printf("stripe=%d, drawex = %d\n",stripe, drawex);
//			printf("before while stripe\n");
//				printf("sd[1]%f\n", all->sd[0]);
			while (stripe < drawex)
			{
//				printf("sd[1]%f\n", all->sd[0]);
				int texX = (int)(256 * (stripe - (-spr_w / 2 + sprite_screen_x)) * TW / spr_w) / 256;
//				printf("transform_y = %f, zbuf[%d] %f, \n",transform_y, stripe, all->zbuf[stripe]);
				if (transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < all->zbuf[stripe])
				{
					int y = drawsy;
//					printf("y = %d\n", y);
					while (y < drawey)
					{
						int d = (y) * 256 - HEIGHT * 128 + spr_h * 128;
//						printf("spr_h = %d, d = %d\n", spr_h, d);
						int texY = ((d * TH) / spr_h) / 256;
						unsigned color = all->texture[4][TW * texY + texX];
//						printf("stripe=%d\n",stripe);
						if ((color & 0x00FFFFFF) != 0)
						   	all->buffer[y][stripe] = color;
						y++;
					}
				}
				stripe++;
			}
			i++;
		}
/*
*/
		draw_buffer(&all->img, all);
		y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while(x < WIDTH)
			{
				all->buffer[y][x] = 0;
				x++;
			}
			y++;
		}
}

int		key_press(int key, t_all *all)
{
//	printf("%d\n", key);
	distributor(key, all);
	return (key);
}
