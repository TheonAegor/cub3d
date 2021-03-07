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
	draw_map_scale(all, point, img);
/*
-------------Нарисовать игрока отдельно------------------------
*/
	draw_plr(img, all->plr.x, all->plr.y, all->plr.angle, all);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img,0, 0);
}

void	draw_plr2(t_data *img, float px, float py, float pa, t_all *all)
{
	float ra,rx,ry,xo,yo;
	int r,mx,my,mp,dof;

	ra = pa;
	r = 0;
	while (r<1)
	{
		dof = 0;	
		float aTan = -1/tan(angle_to_rad(ra));
		if (pa < 180)
		{
			ry = floor(py/SCALE);
			rx = px - (py-ry)/tan(angle_to_rad(ra));
			yo = -(SCALE * 1); 
			xo = -yo*aTan;
		}
		if (pa > 180)
		{
			ry = ceil(py/SCALE);
			rx = px - (py-ry)/tan(angle_to_rad(ra));
			yo = (SCALE * 1); 
			xo = -yo*aTan;
		}
		if (ra == 0 || ra == 180 || ra == 360)
		{
			rx=px;
			ry=py;
			dof=8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			printf("mx=%d, my=%d\n", mx, my);
			dof++;
		}
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
/*
//				distt = distt*cos(angle_to_rad(ang_dif));
	//			printf("%d\n", distt);
				if  ((((int)ceil(yy) % (SCALE * 1) == 0) || ((int)yy % (SCALE * 1) == 0)) && (((int)ceil(xx) % (SCALE * 1) != 0) && ((int)xx % (SCALE * 1) != 0)))
				else if ((((int)ceil(yy) % (SCALE * 1) != 0) && ((int)yy % (SCALE * 1) != 0)) && (((int)ceil(xx) % (SCALE * 1) == 0) || ((int)xx % (SCALE * 1) == 0)))
				{
//					printf("yy=%f, yy=%d\n,", yy, (int)ceil(yy));
					draw_the_line(img, &iter, distt, all, 0x660000);
				}
//				printf("iter=%d\n", iter);
*/
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
/*
*/

}

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
