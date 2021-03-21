#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# define PI 3.14159265359
# define PI2 PI/2
# define PI3 3*PI2
# define MAX_RAY 100 
# define MS 0.1 
# define TW 64 
# define TH 64 
# define START 0
# define VIEW 60
# define DIRECTION PI 
# define WIDTH 1024
# define HEIGHT 720
# define W 119//13
# define A 97//0 
# define S 115//1
# define D 100//2 
# define T 116//2 
# define SCALE 64
# define BLACK 0x000000 
# define WALL 0xFFFFFF 
# define PLR 255 
# define NS 19
# define VMV 0.0
# define VDIV 1 
# define UDIV 1 
# define NTEX 13 


typedef struct s_sprites
{
	double	first;
	int		second;
}				t_sprites;

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
	double			x;
	double			y;
	int			max_x;
}				t_point;

typedef struct	s_sprite
{
	double			x;
	double			y;
	int				texture;
}				t_sprite;

typedef struct s_image_e
{
	void		*img;
	char		*path;
	char		*addr;
	int			img_w;
	int			img_h;
	int			bpp;
	int			llen;
	int			end;
	char		*filename[NTEX];
}				t_image_e;

typedef struct s_color
{
	unsigned long floor;
	unsigned long ceil;
}				t_color;

typedef struct	s_all
{
	char		**map;
	t_point		point;
	t_vars		vars;
	t_data		img;
	t_point		plr;
	t_image_e	image_e;
	t_sprite	sprite[NS];
	t_color		color;
	int			w;
	int			h;
	int			map_row;
	int			sow;//side of the world
	char		*no;
	char		*we;
	char		*sou;
	char		*ea;
	char		*sp;
	char		*floor_c;
	char		*ceil_c;
	double		dx;
	double		dy;
	double		planex;
	double		planey;
	double		zbuf[WIDTH];
	int			so[NS];//sprite Order
	double		sd[NS];//sprite Distanse
	unsigned	texture[NTEX][TW*TH];
	unsigned	buffer[HEIGHT][WIDTH];	
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
void    draw_plr2(t_data *img, t_all *all);
int     key_press(int key, t_all *all);
int     draw_screen_scale(t_all *all, t_point *point, t_data *img);
int     draw_map_scale(t_all *all, t_point *point, t_data *img);
void     find_plr(t_all *all);
int     draw_only_map_scale(t_all *all, t_point *point, t_data *img);
int		draw_line_cubes(t_all *all, t_data *img);
void    clear_img2(t_data *img, int w, int h);
void    distributor(int key, t_all *all);
float	angle_to_rad(float degree);
void	draw_the_line(t_data *img, int *iter, float line_h, t_all *all, int color);
void	draw3D(t_all *all);
float	dist(float x, float y, float xx, float yy);
void draw_the_line2(t_data *img, double px, double py, float rx, float ry);
void	draw_lines(t_data *img, int ds, int de, int x, int color);
void draw_buffer(t_data *img,t_all *all);
void sort_sprites(int *so, double *ds, t_all *all);
int		parse_map(t_all *all);
int		parse_r(char *res, int *w, int *l, int *full);
int		parse_side(char *path_no, char **side, int *full, int flag);
int		check_bounds(t_all all);
int		find_only_plr(t_all *all);
unsigned	to_hex(char *rgb);

#endif
