/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dda2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:29:23 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 11:56:44 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_and_text(t_dda *dda, t_all *all)
{
	if (dda->side == 0)
		dda->wallx = all->plr.y + dda->pwd * dda->rdy;
	else
		dda->wallx = all->plr.x + dda->pwd * dda->rdx;
	dda->wallx -= floor((dda->wallx));
	dda->texx = (int)(dda->wallx * (double)(TW));
	if (dda->side == 0 && dda->rdx > 0)
		dda->texx = TW - dda->texx - 1;
	if (dda->side == 1 && dda->rdy < 0)
		dda->texx = TW - dda->texx - 1;
	dda->step = 1.0 * TH / dda->lh;
	dda->texpos = (dda->ds - all->h / 2 + dda->lh / 2) * dda->step;
}

void		fill_buf(t_dda *dda, t_all *all)
{
	dda->y = 0;
	while (dda->y < dda->ds && dda->ds < dda->de)
	{
		all->buffer[dda->y][dda->x] = all->color.floor;
		dda->y++;
	}
	dda->y = dda->ds;
	while (dda->y < dda->de)
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

void		find_side(t_dda *dda, t_all *all)
{
	dda->hit = 0;
	if (dda->rdx < 0)
	{
		dda->sx = -1;
		dda->sdx = (all->plr.x - dda->mx) * dda->ddx;
	}
	else
	{
		dda->sx = 1;
		dda->sdx = (dda->mx + 1.0 - all->plr.x) * dda->ddx;
	}
	if (dda->rdy < 0)
	{
		dda->sy = -1;
		dda->sdy = (all->plr.y - dda->my) * dda->ddy;
	}
	else
	{
		dda->sy = 1;
		dda->sdy = (dda->my + 1.0 - all->plr.y) * dda->ddy;
	}
}
