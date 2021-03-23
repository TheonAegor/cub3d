#include "cub3d.h"

t_shot		*ft_init_shot(t_all *all)
{
	t_shot	*takeshot;	

	takeshot = ft_calloc(sizeof(t_shot), 1);
	takeshot->w = all->w;
    takeshot->h = all->h;
	printf("w%d,h%d\n", takeshot->w, takeshot->h);
    takeshot->bitcount = 24;
    takeshot->width_in_bytes = ((takeshot->w * takeshot->bitcount + 31) / 32) * 4;
    takeshot->imagesize = takeshot->width_in_bytes * takeshot->h;
    takeshot->filesize = 54 + takeshot->imagesize;
    return (takeshot);
}

unsigned char       *ft_bitheader(t_all *all)
{
    unsigned char	*header;
    u_int32_t		bisize;
    u_int32_t		bfoffbits;
    u_int16_t		biplanes;

    header =(unsigned char *)ft_calloc(54, sizeof(char));
    bisize = 40;
    bfoffbits = 54;
    biplanes = 1;
    ft_memcpy(header, "BM", 2);						//filetype
    ft_memcpy(header + 2 , &all->shot->filesize, 4);//filesize
    ft_memcpy(header + 10, &bfoffbits, 4);//dataoffset
    ft_memcpy(header + 14, &bisize, 4);//header size
    ft_memcpy(header + 18, &all->shot->w, 4);
    ft_memcpy(header + 22, &all->shot->h, 4);
    ft_memcpy(header + 26, &biplanes, 2);
    ft_memcpy(header + 28, &all->shot->bitcount, 2);
    ft_memcpy(header + 34, &all->shot->imagesize, 4);
    return (header);
}

void                screen_shot(t_all *all)
{
	/*
    ft_move(all);
    ft_update(all, YES);
	*/
	ft_printf("inside scren shot\n");
    all->shot = ft_init_shot(all);
    all->shot->header = ft_bitheader(all);
    screno(all);
}

void                screno(t_all *all)
{
    int x ;
    int y ;
    int row;
    int col;

    x = 0;
    y = 0;
    row = all->shot->h - 1;
    col = 0;
	ft_printf("inside screno\n");
    unsigned char* buf = malloc(all->shot->imagesize);
    while (row >= 0)
    {
        x = 0;
        col = 0;
        while (col <= all->shot->w)
        {
            int red = (my_mlx_get_color2(all->img,x,y) >> 16) & 0xFF;
            int green = (my_mlx_get_color2(all->img,x,y) >> 8) & 0xFF;
            int blue = my_mlx_get_color2(all->img,x,y) & 0xFF;
            buf[row * all->shot->width_in_bytes + col * 3 + 0] = blue;
            buf[row * all->shot->width_in_bytes + col * 3 + 1] = green;
            buf[row * all->shot->width_in_bytes + col * 3 + 2] = red;
//			ft_printf("inside screno loop\nrow = %d, width_in_bytes=%d\n image_size=%d, col = %d, w = %d\n", row, all->shot->width_in_bytes, all->shot->imagesize, col, all->shot->w);
            col++;
            x++;
        }
        row--;
        y++;
    }
    ft_printf("Taking ScreenShoot....\n");
    FILE *image = fopen("screenshot.bmp", "wb");
    ft_printf("ScreenShot Has been saved under The name 'screenshot.bmp']\n");
    fwrite(all->shot->header, 1, 54, image);
    fwrite((char*)buf, 1, all->shot->imagesize, image);
    fclose(image);
    free(buf);
}
