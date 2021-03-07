#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# define PI 3.14159265359
# define MAX_RAY 100 
# define START 0
# define VIEW 60
# define DIRECTION 180
# define WIDTH 2000 
# define HEIGHT 1024
# define W 119//13
# define A 97//0 
# define S 115//1
# define D 100//2 
# define SCALE WIDTH/8/2
# define BLACK 0x000000 
# define WALL 0xFFFFFF 
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
	float			x;
	float			y;
	float		angle;
}				t_point;	

typedef struct s_p
{

	int	x;
	int y;
}				t_p;

typedef struct	s_game
{
	t_vars		vars;
	t_data		img;
	int			distt;
	float		line_h;
}				t_game;

typedef struct	s_all
{
	char		**map;
	t_point		point;
	t_vars		vars;
	t_data		img;
	t_point		plr;
	t_game		game;
	float 		lint_h;
}				t_all;

typedef struct s_point_int
{
	int x;
	int y;
}				t_point_int;

int		key_hook(int keycode, t_vars *vars);
int		close_win(int keycode, t_vars *vars);
int		mouse_hook(int button, int x, int y, t_vars *vars);
int		show_map(t_all *all);
int		clear_img(t_data *img, int w, int l);
int		clear_win(t_all *all, int w, int l);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void	pix_put_plr(t_data *img, float x, float y, int color);
int     my_mlx_pp_scale(t_data *data, t_point *point, int color);
int     my_mlx_pp_shift(int *x, int *y, int flag);
void    draw_plr_scale(t_data *img, float x, float y, int color);
void    draw_plr(t_data *img, float x, float y, float angle, t_all *all);
void    draw_plr2(t_data *img, float x, float y, float angle, t_all *all);
int     key_press(int key, t_all *all);
int     draw_screen_scale(t_all *all, t_point *point, t_data *img);
int     draw_map_scale(t_all *all, t_point *point, t_data *img);
int     draw_only_map_scale(t_all *all, t_point *point, t_data *img);
int		draw_line_cubes(t_all *all, t_data *img);
void    clear_img2(t_data *img, int w, int h);
void    distributor(int key, t_all *all);
float	angle_to_rad(float degree);
void	draw_the_line(t_data *img, int *iter, float line_h, t_all *all, int color);
void	draw3D(t_all *all);
float	dist(float x, float y, float xx, float yy);



#endif
