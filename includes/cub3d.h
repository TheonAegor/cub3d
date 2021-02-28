#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# define PI 3.14
# define START 100
# define WIDTH 1024
# define HEIGHT 720
# define W 119
# define A 97 
# define S 115 
# define D 100 
# define SCALE 20 
# define BLACK 0x000000 
# define WALL 0xffffff 
# define PLR 255 

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			llen;
	int			en;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;	

typedef struct	s_all
{
	char		**map;
	t_point		point;
	t_vars		vars;
	t_data		img;
	t_point		plr;
}				t_all;

int		key_hook(int keycode, t_vars *vars);
int		close_win(int keycode, t_vars *vars);
int		mouse_hook(int button, int x, int y, t_vars *vars);
int		show_map(t_all *all);
int		clear_img(t_data *img, int w, int l);
int		clear_win(t_all *all, int w, int l);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
int     my_mlx_pp_scale(t_data *data, t_point *point, int color);
int     my_mlx_pp_shift(t_point *point, int flag);
void    draw_plr_scale(t_data *img, int x, int y, int color);
void    draw_plr(t_data *img, int x, int y);
int     key_press(int key, t_all *all);
int     draw_screen_scale(t_all *all, t_point *point, t_data *img);
int     draw_map_scale(t_all *all, t_point *point, t_data *img);
int     draw_only_map_scale(t_all *all, t_point *point, t_data *img);
void    clear_img2(t_data *img, int w, int h);
void    distributor(int key, t_all *all);
void    go_up(t_data *img, t_all *all);
int		release_ray(t_all *all);
float	draw_line(t_all *all);



#endif
