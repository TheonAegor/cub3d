#include "cub3d.h"


void	wall_and_text(t_dda *dda, t_all *all)
{
	if (dda->side == 0)
		dda->wallx = all->plr.y + dda->pwd * dda->rdy;
	else
		dda->wallx = all->plr.x + dda->pwd * dda->rdx;
	dda->wallx -= floor((dda->wallx));

	dda->texx = (int)(dda->wallx * (double)(TW));
	if(dda->side == 0 && dda->rdx > 0) 
		dda->texx = TW - dda->texx - 1;
	if(dda->side == 1 && dda->rdy < 0) 
		dda->texx = TW - dda->texx - 1;	
	dda->step = 1.0 * TH/dda->lh;
	dda->texpos = (dda->ds - all->h/2 + dda->lh /2) * dda->step;

}

void	fill_buf(t_dda *dda, t_all *all)
{
	dda->y = 0;
	while (dda->y < dda->ds && dda->ds < dda->de)
	{
		all->buffer[dda->y][dda->x] = all->color.floor;
		dda->y++;
	}
	dda->y = dda->ds;
	while ( dda->y < dda->de)
	{
		dda->texy = (int)dda->texpos & (TH - 1);
		dda->texpos += dda->step;
		dda->color = all->texture[dda->tn][TH * dda->texy + dda->texx];
		if (dda->side == 1) 
			dda->color = (dda->color >> 1) & 8355711;
		all->buffer[dda->y][dda->x] = dda->color;
		dda->y++;
	}
	while (dda->y < all->h)
	{
		all->buffer[dda->y][dda->x] = all->color.ceil;
		dda->y++;
	}
	all->zbuf[dda->x] = dda->pwd;
	dda->x += 1;
}

//void	wall_and_text(t_dda *dda, t_all *all)
