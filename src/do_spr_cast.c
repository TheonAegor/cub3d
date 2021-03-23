#include "cub3d.h"

void	precasting(t_spr_cast *s, t_all *all)
{
	int i;

	i = 0;
	while (i < all->spr.num_spr)
	{
		all->so[i] = i;
		all->sd[i] = ((all->plr.x - all->sprite[i].x) * (all->plr.x - all->sprite[i].x) + (all->plr.y - all->sprite[i].y) * (all->plr.y - all->sprite[i].y));
		i++;
	}
	sort_sprites(all->so, all->sd, all);
}

void	spr_cast1(t_spr_cast *s, t_all *all)
{
	s->spr_x = all->sprite[all->so[s->i]].x - all->plr.x;
	s->spr_y = all->sprite[all->so[s->i]].y - all->plr.y;
	s->inv_d = 1.0 / (all->planex * all->dy - all->dx * all->planey);
	s->tr_x = s->inv_d * (all->dy * s->spr_x - all->dx * s->spr_y);
	s->tr_y = s->inv_d * (-all->planey * s->spr_x + all->planex * s->spr_y);
	s->spr_scr_x = (int)((all->w/2)*(1 + s->tr_x / s->tr_y));
	s->vmv_scr = (int)(VMV / s->tr_y);
	s->spr_h = abs((int)(all->h / s->tr_y)) / VDIV;
	s->drawsy = -s->spr_h / 2 + all->h / 2 + s->vmv_scr;
	if (s->drawsy < 0)
		s->drawsy = 0;
	s->drawey = s->spr_h / 2 + all->h / 2 + s->vmv_scr;
	if (s->drawey >= all->h)
		s->drawey = all->h - 1;
	s->spr_w = abs((int)(all->h / (s->tr_y))) / UDIV;
	s->drawsx = -s->spr_w / 2 + s->spr_scr_x;
	if (s->drawsx < 0) 
		s->drawsx = 0;
	s->drawex = s->spr_w / 2 + s->spr_scr_x;
	if (s->drawex >= all->w)
		s->drawex = all->w - 1;
	s->stripe = s->drawsx;
}

void	spr_cast2(t_spr_cast *s, t_all *all)
{
	while (s->stripe < s->drawex)
	{
		s->texx = (int)(256 * (s->stripe - (-s->spr_w / 2 + s->spr_scr_x)) * TW / s->spr_w) / 256;
		if (s->tr_y > 0 && s->stripe > 0 && s->stripe < all->w && s->tr_y < all->zbuf[s->stripe])
		{
			s->y = s->drawsy;
			while (s->y < s->drawey)
			{
				s->d = (s->y) * 256 - all->h * 128 + s->spr_h * 128;
				s->texy = ((s->d * TH) / s->spr_h) / 256;
				s->color = all->texture[4][TW * s->texy + s->texx];
				if ((s->color & 0x00FFFFFF) != 0)
				   	all->buffer[s->y][s->stripe] = s->color;
				s->y++;
			}
		}
		s->stripe++;
	}
}

void	clear_buffer(t_all *all)
{
	int x;
	int y;

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

