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

int		draw_screen_scale(t_all *all, t_point *point, t_data *img)
{
//	draw_map_scale(all, point, img);
//	draw_map(all, point, img);
//	printf("here\n");
	find_plr(all);
/*
-------------Нарисовать игрока отдельно------------------------
*/
	draw_plr2(img, all->plr.x, all->plr.y, all->plr.angle, all);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}

void	draw_plr2(t_data *img, double px, double py, float pa, t_all *all)
{
	int mx, my, x;
	int i;
	int y;

	i = 0;
		x = 0;
		y = 0;
		while (x < WIDTH)
		{
			double camerax = 2 * x/(double)WIDTH - 1;/**/
			double rdx = all->dx + all->planex * camerax;
			double rdy = all->dy + all->planey * camerax;
			mx = (int)all->plr.x;
			my = (int)all->plr.y;

			double sdy;
			double sdx; //side dist y

			double ddx = (rdy == 0) ? 0 : ((rdx == 0) ? 1 : fabs(1 / rdx));
			double ddy = (rdx == 0) ? 0 : ((rdy == 0) ? 1 : fabs(1 / rdy)); //delta dist y
//			printf("ddx= %f, ddy=%f\n", ddx, ddy);
			double pwd;

			int sx;
			int sy;

			int hit = 0;
			int side; // if x side was hit = 0
			if (rdx < 0)
			{
				sx =  -1;
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
			while ( hit == 0)
			{
				if(sdx < sdy)
				{
					sdx += ddx;
					mx += sx;
					side = 0;
				}
				else 
				{
					sdy += ddy;
					my += sy;
					side = 1;
				}
				if (all->map[mx][my] >= '1' )
					hit = 1;
			}
			if (side == 0)
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
//			printf("ds=%d, de = %d\n", ds, de);
//			printf("dx=%f, dx=%f, plx=%f, ply=%f\n", all->dx, all->dy, all->planex, all->planey);
/*
			int color = 0xff0000;
			if (side == 1)
				color = 0x660000;
			draw_lines(img, ds, de, x, color);
*/
			int tn = all->map[mx][my] - 48 - 1;
	//		printf("tn=%d\n", tn);

			double wallX;
			if (side ==0)
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
			y = ds;
			while ( y < de)
			{
				int texY = (int)texPos & (TH - 1);
				texPos += step;
				unsigned color = all->texture[tn][TH * texY + texX];
				if (side == 1) 
					color = (color >> 1) & 8355711;
				all->buffer[y][x] = color;
		//		if (buffer[y][x] != 0)
		//			printf("(%d,%d):%u\n",x,y, buffer[y][x]);
				y++;
			}
			all->zbuf[x] = pwd;
			x += 1;
		}
//		printf("hererer\n");
/*
		y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while (x < WIDTH)
			{
		        my_mlx_pixel_put(img, x, y, buffer[y][x]);
				x++;
//				printf("x=%u, y = %u\n", x, y);
		//		printf("%u\n", buffer[y][x]);
			}
			y++;
		}
*/
//		printf("here before\n");
/*
 * draw_buffer(&all->img, all);
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
*/
/*---SPRITE casting
 *---
*/
//		printf("plr(%f:%f)\nsd(%f,%d)\n", all->plr.x, all->plr.y, all->sd[i], all->so[i]);
		i = 0;
		while (i < NS)
		{
			all->so[i] = i;
			all->sd[i] = ((all->plr.x - all->sprite[i].x) * (all->plr.x - all->sprite[i].x) + (all->plr.y - all->sprite[i].y) * (all->plr.y - all->sprite[i].y));
//			printf("plr(%f:%f)\nsd(%f,%d)\n", all->plr.x, all->plr.y, all->sd[i], all->so[i]);
			i++;
		}
		sort_sprites(all->so, all->sd, all);
//		printf("after_sort\n");
		i = 0;
		while (i < NS)
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
						unsigned color = all->texture[all->sprite[all->so[i]].texture][TW * texY + texX];
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
