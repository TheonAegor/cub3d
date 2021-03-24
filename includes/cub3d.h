/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taegor <taegor@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:23:33 by taegor            #+#    #+#             */
/*   Updated: 2021/03/24 12:27:15 by taegor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "ft_printf.h"
# include <mlx.h>
# include <math.h>

# define MS 0.1
# define TW 64
# define TH 64
# define W 119
# define A 97
# define S 115
# define D 100
# define T 116
# define PLR 255
# define NS 19
# define VMV 0.0
# define VDIV 1
# define UDIV 1
# define NTEX 13

typedef struct		s_sprites
{
	double			first;
	int				second;
}					t_sprites;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				llen;
	int				en;
}					t_data;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct		s_point
{
	double			x;
	double			y;
	int				max_x;
}					t_point;

typedef struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_image_e
{
	void			*img;
	char			*path;
	char			*addr;
	int				img_w;
	int				img_h;
	int				bpp;
	int				llen;
	int				end;
}					t_image_e;

typedef struct		s_color
{
	unsigned long	floor;
	unsigned long	ceil;
}					t_color;

typedef struct		s_brd
{
	int				map_row;
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
	int				max;
}					t_brd;

typedef struct		s_spr
{
	int				num_spr;
}					t_spr;

typedef struct		s_dda
{
	int				x;
	int				y;
	int				mx;
	int				my;
	int				sy;
	int				sx;
	int				hit;
	int				side;
	int				lh;
	int				ds;
	int				de;
	int				tn;
	int				texx;
	int				texy;
	double			camerax;
	double			rdx;
	double			rdy;
	double			sdy;
	double			sdx;
	double			ddx;
	double			ddy;
	double			pwd;
	double			step;
	double			texpos;
	double			wallx;
	unsigned		color;

}					t_dda;

typedef struct		s_spr_cast
{
	double			spr_x;
	double			spr_y;
	double			inv_d;
	double			tr_x;
	double			tr_y;
	int				spr_scr_x;
	int				vmv_scr;
	int				spr_h;
	int				drawsy;
	int				drawey;
	int				spr_w;
	int				drawsx;
	int				drawex;
	int				stripe;
	int				texx;
	int				i;
	int				y;
	int				d;
	int				texy;
	unsigned		color;
}					t_spr_cast;

typedef struct		s_rc
{
	int				row;
	int				col;
}					t_rc;

typedef struct		s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct		s_shot
{
	int				w;
	int				h;
	unsigned		bitcount;
	unsigned		wibs;
	unsigned		imagesize;
	unsigned		filesize;
	unsigned char	*header;
}					t_shot;

typedef struct		s_all
{
	int				w;
	int				h;
	int				sow;
	int				save;
	int				so[NS];
	char			**map;
	char			*no;
	char			*we;
	char			*sou;
	char			*ea;
	char			*sp;
	char			*floor_c;
	char			*ceil_c;
	float			lint_h;
	double			dx;
	double			dy;
	double			planex;
	double			planey;
	double			*zbuf;
	double			sd[NS];
	unsigned		texture[NTEX][TW * TH];
	unsigned		**buffer;
	t_point			point;
	t_vars			vars;
	t_data			img;
	t_point			plr;
	t_image_e		image_e;
	t_spr			spr;
	t_sprite		*sprite;
	t_color			color;
	t_brd			brd;
	t_shot			*shot;
}					t_all;

t_shot				*ft_init_shot(t_all *all);
unsigned char		*ft_bitheader(t_all *all);
unsigned			to_hex(char *rgb);
unsigned int		my_mlx_get_color2(t_data data, int x, int y);
void				draw_plr_scale(t_data *img, float x, float y, int color);
void				draw_plr2(t_data *img, t_all *all);
void				my_mlx_pixel_put(t_data *img, int x, int y, int color);
void				pix_put_plr(t_data *img, float x, float y, int color);
void				find_plr(t_all *all);
void				clear_img2(t_data *img, int w, int h);
void				distributor(int key, t_all *all);
void				draw_buffer(t_data *img, t_all *all);
void				sort_sprites(int *so, double *ds, t_all *all);
void				free_map(t_all *all);
void				free_buf_z(t_all *all);
void				free_all(t_all *all);
void				count_sprites(t_all *all);
void				start_init(t_all *all);
void				handle_plr_errors(int error, t_all *all);
void				error_forbid_char(t_all *all);
void				error_filename(int err, t_all *all);
void				handle_arg_errors(int error);
void				handle_parse_err(int err, t_all *all);
void				handle_hex_err(int err, t_all *all);
void				handle_hex_err2(int err, t_all *all);
void				handle_map_errors(int x, int y, t_all *all);
void				middle_init(t_all *all);
void				start_dda(t_dda *dda, t_all *all);
void				find_side(t_dda *dda, t_all *all);
void				find_hit(t_dda *dda, t_all *all);
void				find_start_end(t_dda *dda, t_all *all);
void				determine_num_texture(t_dda *dda, t_all *all);
void				wall_and_text(t_dda *dda, t_all *all);
void				fill_buf(t_dda *dda, t_all *all);
void				precasting(t_spr_cast *s, t_all *all);
void				spr_cast1(t_spr_cast *s, t_all *all);
void				spr_cast2(t_spr_cast *s, t_all *all);
void				clear_buffer(t_all *all);
void				screen_shot(t_all *all);
void				screno(t_all *all);
void				push_img_to_texture(char *path, int num, t_all *all);
void				push_img_to_texture(char *path, int num, t_all *all);
void				define_direction(t_all *all);
float				angle_to_rad(float degree);
float				dist(float x, float y, float xx, float yy);
int					key_press(int key, t_all *all);
int					draw_screen_scale(t_all *all, t_point *point, t_data *img);
int					draw_map_scale(t_all *all, t_point *point, t_data *img);
int					draw_only_map_scale(t_all *all, t_point *point,
		t_data *img);
int					draw_line_cubes(t_all *all, t_data *img);
int					key_hook(int keycode, t_vars *vars);
int					close_win(int keycode, t_vars *vars);
int					mouse_hook(int button, int x, int y, t_vars *vars);
int					show_map(t_all *all);
int					clear_img(t_data *img, int w, int l);
int					clear_win(t_all *all, int w, int l);
int					my_mlx_pp_scale(t_data *data, t_point *point, int color);
int					my_mlx_pp_shift(int *x, int *y, int flag);
int					parse_map(t_all *all);
int					parse_r(char *res, int *w, int *l, int *full);
int					parse_side(char *path_no, char **side, int *full, int flag);
int					check_bounds(t_all all, t_brd *brd, int x);
int					find_only_plr(t_all *all);
int					check_bounds2(t_all *all, t_brd *brd);
int					create_spr_tabl(t_all *all);
int					exit_buf(t_all *all);
int					check_two_str(char *str1, char *str2);
int					if_forbid_chars(int c, char *forbid_chars);
int					check_commas(char *str, t_all *all);
int					check_hex(t_all *all);
int					check_chars(char *str);
int					parse_elems(t_all *all, int *full, int i);
int					help_with_hex(t_all *all, int full);
int					if_nswe(t_all *all, int i, int j, int *flag);
int					exit_but(t_all *all);
int					make_map(t_list **head, size_t size, t_all *all);

#endif
