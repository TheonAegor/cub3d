# include "libft.h"
# include <mlx.h>
# include <math.h>

typedef struct s_image
{
	void        *img;
    char        *path;
    char        *addr;
    int         img_width;
    int         img_height;
    int         bpp;
    int         line_len;
    int         end;
}			t_image;

typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bpp;
    int         llen;
    int         en;
}               t_data;

typedef struct  s_vars
{
    void        *mlx;
    void        *win;
}               t_vars;

