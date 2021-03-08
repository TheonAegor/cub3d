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

	x = 0;
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
				if (all->map[mx][my] == '1' )
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
			printf("dx=%f, dx=%f, plx=%f, ply=%f\n", all->dx, all->dy, all->planex, all->planey);
			int color = 0xff0000;
			if (side == 1)
				color = 0x660000;
			draw_lines(img, ds, de, x, color);
			x += 1;
		}
}
/*
void	draw_plr2(t_data *img, float px, float py, float pa, t_all *all)
{
	float ra,rx,ry,xo,yo,aTan,nTan;
	int r,mx,my,mp,dof;

	ra = pa;
	r = 0;
	aTan = 0;
	nTan = 0;
//	printf("tan(PI)%f\n", tan(PI));
	while (r<1)
	{
		dof = 0;	
		if (ra != PI || ra != 0)
		{
			aTan = 1/tan(ra);
			nTan = -tan(ra);
		}
		printf("aTan=%f\n", aTan);
		if (ra < PI)
		{
			ry = (((int)py>>6)<<6)-0.001;
			rx = (py-py)*aTan+px;
			yo = -(SCALE * 1); 
			xo = -yo*aTan;
			printf("r(%f;%f):o(%f;%f)\n", rx,ry,xo,yo);
		}
		if (ra > PI)
		{
			ry = (((int)py>>6)<<6)+(SCALE * 1);
			rx = -(py-ry)*aTan+px;
			yo = (SCALE * 1); 
			xo = -yo*aTan;
		}
		printf("nTan=%f\n", nTan);
		if (ra > PI2 && ra < PI3)
		{
			rx = (((int)px>>6)<<6)-0.001;
			ry = (px-rx)*nTan+py;
			xo = -(SCALE * 1); 
			yo = -xo*nTan;
			printf("r(%f;%f):o(%f;%f)\n", rx,ry,xo,yo);
		}
		if (ra < PI2 || ra > PI3)
		{
			rx = (((int)px>>6)<<6)+(SCALE * 1);
			ry = (px-rx)*nTan+py;
			xo = (SCALE * 1); 
			yo = -xo*nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx=px;
			ry=py;
			dof=8;
		}
		while (dof < 8)
		{
			if (rx > WIDTH)
				rx = SCALE;
			if (rx < 0)
				rx = 0;
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			printf("rx=%f, ry=%f\n", rx, ry);
			printf("mx=%d, my=%d\n", mx, my);
			if (all->map[my][mx] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
//		printf("mx=%d, my=%d\n", mx, my);
//		printf("px=%f, py=%f,rx=%f, ry=%f\n",px, py, rx, ry);
		draw_the_line2(img, px, py, rx, ry);
		r++;
	}
}


void	draw_plr(t_data *img, float x, float y, float angle, t_all *all)
{
	char *dst;
	float ang_rng_top;
	float ang_rng_low;
	float xx;
	float yy;
	float distt;
	float line_h;
	float line_h_end;
	int iter;
	int ang_dif;

	ang_rng_top = angle + VIEW/2;
	ang_rng_low = angle - VIEW/2;
	xx = x;
	yy = y;
	line_h = 0;
	line_h_end = 1000;
	iter = 0;
	while (ang_rng_low < ang_rng_top)
	{
		xx = x;
		yy = y;
		while (xx < WIDTH/2 && yy < WIDTH/2)
		{
//			printf("y=%f,scale=%d, =%f\n",yy, SCALE, yy / (SCALE * 1));
			if (all->map[(int)(floor(yy/(SCALE * 1)))][(int)(floor(xx/(SCALE * 1)))] == '1')
			{
//				printf("xx=%f, yy=%f", xx, yy);
				ang_dif = abs(ang_rng_low - angle);
//				printf("dif=%d, an=%f, low=%f, cos%f\n", ang_dif, angle, ang_rng_low, cos(angle_to_rad(ang_dif)));
				distt = (SCALE*HEIGHT)/(dist(x, y, xx, yy)*cos(angle_to_rad(ang_dif)))/3;
				if (distt > HEIGHT)
					distt = HEIGHT;
				if (((int)yy % (SCALE * 1) == 0))
					draw_the_line(img, &iter, distt, all, 0xff0000);
				else 
					draw_the_line(img, &iter, distt, all, 0x660000);
//				distt = distt*cos(angle_to_rad(ang_dif));
	//			printf("%d\n", distt);
				if  ((((int)ceil(yy) % (SCALE * 1) == 0) || ((int)yy % (SCALE * 1) == 0)) && (((int)ceil(xx) % (SCALE * 1) != 0) && ((int)xx % (SCALE * 1) != 0)))
				else if ((((int)ceil(yy) % (SCALE * 1) != 0) && ((int)yy % (SCALE * 1) != 0)) && (((int)ceil(xx) % (SCALE * 1) == 0) || ((int)xx % (SCALE * 1) == 0)))
				{
//					printf("yy=%f, yy=%d\n,", yy, (int)ceil(yy));
					draw_the_line(img, &iter, distt, all, 0x660000);
				}
//				printf("iter=%d\n", iter);
				break ;
			}
//			printf("here\n");
			dst = img->addr + ((int)yy * img->llen + (int)xx * img->bpp / 8);
			pix_put_plr(img, xx, yy, 0xff0000);
			xx -= cos(angle_to_rad(ang_rng_low));
			yy -= sin(angle_to_rad(ang_rng_low));
		}
		ang_rng_low += 0.5;
	}

}
*/

void	draw_plr_scale(t_data *img, float x, float y, int color)
{
	int scale_y;
	int scale_x;

//	printf("x = %f, y= %f, SCALE = %d, col = %d\n", x, y, SCALE, color);
	scale_y = y + 10;
	scale_x = x + 10;
//	printf("scl_x=%d, scl_y=%d\n", scale_x, scale_y);
	while ((int)y < scale_y)
	{
		while ((int)x < scale_x)
		{
			pix_put_plr(img, x, y, color);
			x++;
		}
		x = x - 10;
		y++;
	}

}

int		key_press(int key, t_all *all)
{
	printf("%d\n", key);
	distributor(key, all);
	return (key);
}
