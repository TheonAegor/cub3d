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
	printf("w=%d,h=%d\n", *w, *h);
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
	t_dda	dda;

	i = 0;
		x = 0;
		y = 0;
//		printf("all-w=%d, all-h=%d\n", all->w, all->h);
		while (x < all->w)
		{
//			printf("start:dx=%f, dy = %f\n", all->dx, all->dy);
			dda.camerax = 2 * x/(double)all->w - 1;/**/
			dda.rdx = all->dx + all->planex * dda.camerax; /*Ray dir x*/
			dda.rdy = all->dy + all->planey * dda.camerax;
//			printf("rdy=%f, rdx = %f\n", dda.rdy, rdx);
			mx = (int)floor(all->plr.x);
			my = (int)floor(all->plr.y);

			dda.sdy;
			dda.sdx; //side dist y

			dda.ddx = (dda.rdy == 0) ? 0 : ((dda.rdx == 0) ? 1 : fabs(1 / dda.rdx));
			dda.ddy = (dda.rdx == 0) ? 0 : ((dda.rdy == 0) ? 1 : fabs(1 / dda.rdy)); //delta dist y
/*
*/
			dda.pwd;

			dda.sx; //step x
			dda.sy;

			dda.hit = 0;
			dda.side; // if x side was hit = 0
			if (dda.rdx < 0)
			{
				dda.sx = -1;
				dda.sdx = (all->plr.x - mx) * dda.ddx;
			}
			else
			{
				dda.sx = 1;
				dda.sdx = (mx + 1.0 - all->plr.x) * dda.ddx;
			}
			if (dda.rdy < 0)
			{
				dda.sy = -1;
				dda.sdy = (all->plr.y - my) * dda.ddy;
			}	
			else 
			{
				dda.sy = 1;
				dda.sdy = (my + 1.0 - all->plr.y) * dda.ddy;
			}
/*
			printf("dx=%f, dy = %f\n", all->dx, all->dy);
			printf("rdx=%f, rdy = %f\n", dda.rdx, dda.rdy);
			printf("ddx= %f, ddy=%f\n", dda.ddx, dda.ddy);
			printf("sdx=%f, sdy = %f\n", dda.sdx, dda.sdy);
			printf("mx= %d, my =%d\n", mx, my);
			printf("x=%d\n", x);
*/
			while ( dda.hit == 0)
			{
				if(dda.sdx < dda.sdy)
				{
					dda.sdx += dda.ddx;
					mx += dda.sx;
					dda.side = 0;
//					printf("here1\n");
				}
				else 
				{
					dda.sdy += dda.ddy;
					my += dda.sy;
					dda.side = 1;
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
					dda.hit = 1;
//					printf("here3\n");
				}
//				printf("inside hit\n");
			}
			if (dda.side == 0)
		/*-------y distance------*/
				dda.pwd = (mx - all->plr.x + (1 - dda.sx)/ 2) / dda.rdx;
			else 
				dda.pwd = (my - all->plr.y + (1 - dda.sy) / 2)/ dda.rdy;

			dda.lh = (int)(all->h / dda.pwd);
			dda.ds = -dda.lh / 2 + all->h /2; //draw start
			if (dda.ds < 0)
				dda.ds = 0;
			dda.de = dda.lh / 2 + all->h / 2; //draw end
			if (dda.de >= all->h)
				dda.de = all->h - 1;
/*
			printf ("ds = %d\n", dda.ds);
			printf("ds=%d, de = %d\n", dda.ds, dda.de);
			printf("dx=%f, dx=%f, plx=%f, ply=%f\n", all->dx, all->dy, all->planex, all->planey);
			int color = 0xff0000;
			if (side == 1)
				color = 0x660000;
			draw_lines(img, ds, de, x, color);
*/
			dda.tn = all->map[my][mx] - 48 - 1;
			if (dda.rdy > 0)
			{
				dda.tn = 0; 
				if (dda.rdx > 0)
				{
					if (dda.side == 0)
						dda.tn = 2;
				}
				else
				{
					if (dda.side == 0)
						dda.tn = 3;
				}
			}
			else
			{
				dda.tn = 1;
				if (dda.rdx > 0)
				{
					if (dda.side == 0)
						dda.tn = 2;
				}
				else
				{
					if (dda.side == 0)
						dda.tn = 3;
				}
			}
	//		printf("tn=%d\n", dda.tn);

			dda.wallx;
			if (dda.side == 0)
				dda.wallx = all->plr.y + dda.pwd * dda.rdy;
			else
				dda.wallx = all->plr.x + dda.pwd * dda.rdx;
			dda.wallx -= floor((dda.wallx));

			dda.texx = (int)(dda.wallx * (double)(TW));
			if(dda.side == 0 && dda.rdx > 0) 
				dda.texx = TW - dda.texx - 1;
			if(dda.side == 1 && dda.rdy < 0) 
				dda.texx = TW - dda.texx - 1;	
			dda.step = 1.0 * TH/dda.lh;
			dda.texpos = (dda.ds - all->h/2 + dda.lh /2) * dda.step;
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
			printf("rdx=%f, rdy = %f\n", rdx, dda.rdy);
			printf("ddx= %f, ddy=%f\n", dda.ddx, dda.ddy);
			printf("mx= %d, my =%d\n", mx, my);
			printf("outside\n");
*/
			y = 0;
			while (y < dda.ds && dda.ds < dda.de)
			{
				all->buffer[y][x] = all->color.floor;
				y++;
			}
			y = dda.ds;
			while ( y < dda.de)
			{
				dda.texy = (int)dda.texpos & (TH - 1);
				dda.texpos += dda.step;
				dda.color = all->texture[dda.tn][TH * dda.texy + dda.texx];
				if (dda.side == 1) 
					dda.color = (dda.color >> 1) & 8355711;
				all->buffer[y][x] = dda.color;
				y++;
			}
			while (y < all->h)
			{
				all->buffer[y][x] = all->color.ceil;
				y++;
			}
			all->zbuf[x] = dda.pwd;
			x += 1;
		}
/*----------------------SPRITE casting-----------------------
 *---*/
//		printf("plr(%f:%f)\nsd(%f,%d)\n", all->plr.x, all->plr.y, all->sd[i], all->so[i]);
		i = 0;
		t_spr_cast	s;
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
			int sprite_screen_x = (int)((all->w/2)*(1 + transform_x / transform_y));
			int vmove_screen = (int)(VMV / transform_y);
			int spr_h = abs((int)(all->h / transform_y)) / VDIV;
			int drawsy = -spr_h / 2 + all->h / 2 + vmove_screen;
			if (drawsy < 0)
				drawsy = 0;
			int drawey = spr_h / 2 + all->h / 2 + vmove_screen;
			if (drawey >= all->h)
				drawey = all->h - 1;
			int spr_w = abs((int)(all->h / (transform_y))) / UDIV;
			int drawsx = -spr_w / 2 + sprite_screen_x;
			if (drawsx < 0) 
				drawsx = 0;
			int drawex = spr_w / 2 + sprite_screen_x;
			if (drawex >= all->w)
				drawex = all->w - 1;
			int stripe = drawsx;
//			printf("stripe=%d, drawex = %d\n",stripe, drawex);
//			printf("before while stripe\n");
//				printf("sd[1]%f\n", all->sd[0]);
			while (stripe < drawex)
			{
//				printf("sd[1]%f\n", all->sd[0]);
				int texX = (int)(256 * (stripe - (-spr_w / 2 + sprite_screen_x)) * TW / spr_w) / 256;
//				printf("transform_y = %f, zbuf[%d] %f, \n",transform_y, stripe, all->zbuf[stripe]);
				if (transform_y > 0 && stripe > 0 && stripe < all->w && transform_y < all->zbuf[stripe])
				{
					int y = drawsy;
//					printf("y = %d\n", y);
					while (y < drawey)
					{
						int d = (y) * 256 - all->h * 128 + spr_h * 128;
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
		while (y < all->h)
		{
			x = 0;
			while(x < all->w)
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
