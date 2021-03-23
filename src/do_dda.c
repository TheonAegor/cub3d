/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:12:22 by taegor            #+#    #+#             */
/*   Updated: 2021/03/23 10:16:05 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_dda(t_dda *dda, t_all *all)
{
	dda->camerax = 2 * dda->x/(double)all->w - 1;/**/
	dda->rdx = all->dx + all->planex * dda->camerax;
	dda->rdy = all->dy + all->planey * dda->camerax;
	dda->mx = (int)floor(all->plr.x);
	dda->my = (int)floor(all->plr.y);
	dda->ddx = (dda->rdy == 0) ? 0 : ((dda->rdx == 0) ? 1 : fabs(1 / dda->rdx));
	dda->ddy = (dda->rdx == 0) ? 0 : ((dda->rdy == 0) ? 1 : fabs(1 / dda->rdy)); //delta dist y

}

void	find_side(t_dda *dda, t_all *all)
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

void	find_hit(t_dda *dda, t_all *all)
{
	while (dda->hit == 0)
	{
		if(dda->sdx < dda->sdy)
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
		dda->pwd = (dda->mx - all->plr.x + (1 - dda->sx)/ 2) / dda->rdx;
	else 
		dda->pwd = (dda->my - all->plr.y + (1 - dda->sy) / 2)/ dda->rdy;
}

void	find_start_end(t_dda *dda, t_all *all)
{
	dda->lh = (int)(all->h / dda->pwd);
	dda->ds = -dda->lh / 2 + all->h /2; //draw start
	if (dda->ds < 0)
		dda->ds = 0;
	dda->de = dda->lh / 2 + all->h / 2; //draw end
	if (dda->de >= all->h)
		dda->de = all->h - 1;
}

void	determine_num_texture(t_dda *dda, t_all *all)
{
	dda->tn = all->map[dda->my][dda->mx] - 48 - 1;
	if (dda->rdy > 0)
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
    		
    		
    		
    		
    		
    		
    		
    		
    		
    		
    		
    		
    		
    		
