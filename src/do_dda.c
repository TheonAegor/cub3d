/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:12:22 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 08:51:18 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		start_dda(t_dda *dda, t_all *all)
{
	dda->camerax = 2 * dda->x / (double)all->w - 1;
	dda->rdx = all->dx + all->planex * dda->camerax;
	dda->rdy = all->dy + all->planey * dda->camerax;
	dda->mx = (int)floor(all->plr.x);
	dda->my = (int)floor(all->plr.y);
	if (dda->rdy == 0)
		dda->ddx = 0;
	else if (dda->rdx == 0)
		dda->ddx = 1;
	else
		dda->ddx = fabs(1 / dda->rdx);
	if (dda->rdx == 0)
		dda->ddy = 0;
	else if (dda->rdy == 0)
		dda->ddy = 1;
	else
		dda->ddy = fabs(1 / dda->rdy);
}

void		find_hit(t_dda *dda, t_all *all)
{
	while (dda->hit == 0)
	{
		if (dda->sdx < dda->sdy)
		{
			dda->sdx += dda->ddx;
			dda->mx += dda->sx;
			dda->side = 0;
		}
		else
		{
			dda->sdy += dda->ddy;
			dda->my += dda->sy;
			dda->side = 1;
		}
		if (all->map[dda->my][dda->mx] == '1')
			dda->hit = 1;
	}
	if (dda->side == 0)
		dda->pwd = (dda->mx - all->plr.x + (1 - dda->sx) / 2) / dda->rdx;
	else
		dda->pwd = (dda->my - all->plr.y + (1 - dda->sy) / 2) / dda->rdy;
}

void		find_start_end(t_dda *dda, t_all *all)
{
	dda->lh = (int)(all->h / dda->pwd);
	dda->ds = -dda->lh / 2 + all->h / 2;
	if (dda->ds < 0)
		dda->ds = 0;
	dda->de = dda->lh / 2 + all->h / 2;
	if (dda->de >= all->h)
		dda->de = all->h - 1;
}

static void	rdy_bigger(t_dda *dda)
{
	dda->tn = 0;
	if (dda->rdx > 0)
	{
		if (dda->side == 0)
			dda->tn = 2;
	}
	else
	{
		if (dda->side == 0)
			dda->tn = 3;
	}
}

void		determine_num_texture(t_dda *dda, t_all *all)
{
	dda->tn = all->map[dda->my][dda->mx] - 48 - 1;
	if (dda->rdy > 0)
		rdy_bigger(dda);
	else
	{
		dda->tn = 1;
		if (dda->rdx > 0)
		{
			if (dda->side == 0)
				dda->tn = 2;
		}
		else
		{
			if (dda->side == 0)
				dda->tn = 3;
		}
	}
}
