/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:58:09 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 10:07:02 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_shot				*ft_init_shot(t_all *all)
{
	t_shot			*takeshot;

	takeshot = ft_calloc(sizeof(t_shot), 1);
	takeshot->w = all->w;
	takeshot->h = all->h;
	takeshot->bitcount = 24;
	takeshot->width_in_bytes = ((takeshot->w *
				takeshot->bitcount + 31) / 32) * 4;
	takeshot->imagesize = takeshot->width_in_bytes * takeshot->h;
	takeshot->filesize = 54 + takeshot->imagesize;
	return (takeshot);
}

unsigned char		*ft_bitheader(t_all *all)
{
	unsigned char	*header;
	u_int32_t		bisize;
	u_int32_t		bfoffbits;
	u_int16_t		biplanes;

	header = (unsigned char *)ft_calloc(54, sizeof(char));
	bisize = 40;
	bfoffbits = 54;
	biplanes = 1;
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &all->shot->filesize, 4);
	ft_memcpy(header + 10, &bfoffbits, 4);
	ft_memcpy(header + 14, &bisize, 4);
	ft_memcpy(header + 18, &all->shot->w, 4);
	ft_memcpy(header + 22, &all->shot->h, 4);
	ft_memcpy(header + 26, &biplanes, 2);
	ft_memcpy(header + 28, &all->shot->bitcount, 2);
	ft_memcpy(header + 34, &all->shot->imagesize, 4);
	return (header);
}

void				screen_shot(t_all *all)
{
	ft_printf("inside scren shot\n");
	all->shot = ft_init_shot(all);
	all->shot->header = ft_bitheader(all);
	screno(all);
}

void				screno(t_all *all)
{
	t_point			xy;
	t_rc			rc;
	t_rgb			rgb;
	unsigned char	*buf;
	int				fd;
	FILE			*image;

	xy.y = 0;
	rc.row = all->shot->h;
	buf = malloc(all->shot->imagesize);
	while (rc.row >= 0)
	{
		xy.x = 0;
		rc.col = 0;
		while (rc.col <= all->shot->w)
		{
			rgb.red = (my_mlx_get_color2(all->img, xy.x, xy.y) >> 16) & 0xFF;
			rgb.green = (my_mlx_get_color2(all->img, xy.x, xy.y) >> 8) & 0xFF;
			rgb.blue = my_mlx_get_color2(all->img, xy.x, xy.y) & 0xFF;
			buf[rc.row * all->shot->width_in_bytes + rc.col * 3 + 0] = rgb.blue;
			buf[rc.row * all->shot->width_in_bytes +
				rc.col * 3 + 1] = rgb.green;
			buf[rc.row * all->shot->width_in_bytes + rc.col * 3 + 2] = rgb.red;
			rc.col++;
			xy.x++;
		}
		rc.row--;
		xy.y++;
	}
	ft_printf("Taking ScreenShoot....\n");
	fd = open("screenshot1.bmp", O_CREAT, O_WRONLY | O_TRUNC);
	image = fopen("screenshot.bmp", "wb");
	ft_printf("ScreenShot Has been saved under The name 'screenshot.bmp']\n");
	fwrite(all->shot->header, 1, 54, image);
	write(fd, all->shot->header, 54);
	write(fd, (char *)buf, 10);
	close(fd);
	fwrite((char*)buf, 1, all->shot->imagesize, image);
	fclose(image);
	free(buf);
}
