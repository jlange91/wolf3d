/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:56:39 by jlange            #+#    #+#             */
/*   Updated: 2019/03/05 03:02:21 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/includes/libft.h"
# include "mlx.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# define ESC 53
# define SHIFT 257
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define PLUS 27
# define MINUS 24
# define FISHEYES 3
# define DIST_MINUS 18
# define DIST_PLUS 19
# define FOV_MINUS 20
# define FOV_PLUS 21
# define BLANC 0x00FFFFFF
# define VERT_F 0x428C01
# define VERT_C 0x25FA3A
# define BLEU_F 0x013CFE
# define BLEU_C 0x2BC7FF
# define MARON_F 0x975600
# define MARON_C 0xC37612
# define JAUNE 0xF2F266
# define WIN_X 900
# define WIN_Y 740
# define WIN_X_MINIMAP 250
# define WIN_Y_MINIMAP 200
# define START_ANGLE 60
# define LENGTH_VIEW 20
# define FOV 60
# define MINIMAP_ZOOM 4
# define SPEED_ROT 5
# define SPEED_MOOVE 0.3
# define BLOCKS_PERCENT 95
# define SIZE_INFINY_MAP 1000
# define DISCOVER 1

typedef struct		s_line
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;
}					t_line;

typedef struct		s_point
{
	int x;
	int y;
}					t_point;

typedef struct		s_dpoint
{
	double x;
	double y;
}					t_dpoint;

typedef struct		s_intersection
{
	t_dpoint		point;
	double			dist;
	double			dist_wfe;
	int				wall;
	double			angle;
	unsigned int	color;
	int				hit;
}					t_intersection;

typedef struct		s_image
{
	void			*win;
	void			*mlx_img;
	unsigned int	*img;
	int				width;
	int				height;
	int				bpp;
	int				size_l;
	int				endian;
}					t_image;

typedef struct		s_minimap
{
	double square;
	double restx;
	double resty;
	double px;
	double py;
}					t_minimap;

typedef struct		s_map
{
	int		discover;
	int		type;
}					t_map;

typedef struct		s_wolf
{
	void			*mlx;
	char			*file;
	t_map			**map;
	int				map_width;
	int				map_height;
	double			radius;
	double			posx;
	double			posy;
	double			space_inter_radius;
	int				fisheyes;
	t_image			minimap;
	t_image			screen;
	t_intersection	inter[WIN_X];
	t_image			text[6];
	long double		hpp;
	int				minimapx;
	int				minimapy;
	t_minimap		mm_info;
	int				error;
	int				length_view;
	int				fov;
	double		sec;
	char			key[280];
}					t_wolf;

typedef struct		s_fc
{
	int			y;
	int			drawend;
	double		floor_x_wall;
	double		floor_y_wall;
	double		dist_wall;
	double		current_dist;
	double		weight;
	double		current_floor_x;
	double		current_floor_y;
	int			floor_tex_x;
	int			floor_tex_y;
}					t_fc;

typedef struct		s_m
{
	double			max_x;
	double			max_y;
	t_point			point_a;
	t_point			point_b;
	double			rx;
	double			ry;
	double			dx;
	double			dy;
	double			x;
	double			y;
}					t_m;

typedef struct		s_dc
{
	unsigned int	color;
	int				pixel;
	int				i;
	int				text;
	double			x1;
	double			dist;
}					t_dc;

typedef struct		s_si
{
	t_dpoint	dist;
	t_dpoint	first_dist;
	int			stepx;
	int			stepy;
	int			mapx;
	int			mapy;
	int			hit;
}					t_si;

int					ft_init(t_wolf *wolf, int ac, char **av);
void				ft_free(t_wolf *wolf);
void				ft_error(int error);
int					ft_wolf(t_wolf *wolf);
void				init_textures(t_wolf *wolf);
int					ft_fill_tab(t_wolf *wolf, char **av);
int					ft_display_hook(t_wolf *wolf);
int					ft_redcross(t_wolf *wolf);
void				ft_pixel_put(t_image *img, int x, int y, int color);
void				ft_draw_rectangle(t_point map0, t_point map1,
		t_image	*img, int color);
void				ft_line(t_point map0, t_point map1, t_image *img,
		int color);
t_point				endpoint(double angle, int x1, int y1, double lenght);
t_dpoint			endpoint2(double angle, double x1, double y1,
		double lenght);
double				d_cos(double degree);
double				d_sin(double degree);
double				d_tan(double degree);
t_dpoint			find_dist(double angle);
t_dpoint			find_first_dist(double posx, double posy, double angle);
t_intersection		search_intersection(t_wolf *wolf, t_intersection inter);
void				search_intersections(t_wolf *wolf);
void				ft_search_intersections(t_wolf *wolf);
double				resize_double(double nb);
void				display_minimap(t_wolf *wolf);
void				minimap_draw_angle(t_wolf *wolf);
void				minimap_draw_map(t_wolf *wolf);
void				minimap_draw_perso(t_wolf *wolf);
void				display_screen(t_wolf *wolf);
void				ft_line_wall(t_point map0, t_point map1, t_image *img,
		int color);
void				floor_ceil_casting(t_wolf *wolf, t_intersection *inter,
		int x);
unsigned int		set_color(double dist, unsigned int color, int length_view);
t_si				init_search_intersection(t_wolf *wolf,
		t_intersection inter);
void				forward(t_wolf *wolf);
void				backward(t_wolf *wolf);

int						key_press_hook(int keycode, t_wolf *wolf);
int						key_release_hook(int keycode, t_wolf *wolf);

#endif
