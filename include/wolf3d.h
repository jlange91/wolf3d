/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:56:39 by jlange            #+#    #+#             */
/*   Updated: 2019/01/28 17:53:53 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/includes/libft.h"
# include "mlx.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# define AMP 10
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define ZOOM 12
# define DEZOOM 14
# define PLUS 27
# define MINUS 24
# define PROJECTION 35
# define COLOR 8
# define ROT_Y1 13
# define ROT_X1 0
# define ROT_Y2 1
# define ROT_X2 2
# define ROT_Z1 15
# define FISHEYES 3
# define MUL_COLOR1 6
# define MUL_COLOR2 7
# define BLANC 0x00FFFFFF
# define VERT_F 0x428C01
# define VERT_C 0x25FA3A
# define BLEU_F 0x013CFE
# define BLEU_C 0x2BC7FF
# define MARON_F 0x975600
# define MARON_C 0xC37612
# define JAUNE 0xF2F266

# define WIN_X 1800
# define WIN_Y 1024

#define LENGHT_VIEW 10000
#define FOV 60

# define WIN_X_MINIMAP 250
# define WIN_Y_MINIMAP 200
# define MINIMAP_ZOOM 5

#define START_ANGLE 60

#define SPEED_ROT 5
#define SPEED_MOOVE 0.4

typedef struct		s_line
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;
}									t_line;

typedef struct		s_point
{
	int x;
	int y;
}									t_point;

typedef struct		s_dpoint
{
	double x;
	double y;
}									t_dpoint;

typedef struct		s_intersection
{
	t_dpoint				point;
	double				dist;
	double				dist_wfe; //dist without fisheyes
	int						wall;
	double				angle;
	unsigned int 	color;
	int						hit;
	// hit value :
	// 0 = no touch
	// 1 = nord
	// 2 = sud
	// 3 = est
	// 4 = ouest
}									t_intersection;

typedef struct		s_image
{
	void					*win;
	void					*mlx_img;
	unsigned int	*img;
	int 					width;
	int 					height;
	int						bpb;
	int						size_l;
	int						endian;
}									t_image;

typedef struct		s_minimap
{
	double square;
	double restx;
	double resty;
	double px;
	double py;
}									t_minimap;

typedef struct		s_wolf
{
	void						*mlx;
	char 						*file;
	int							**map;
	int 						mapWidth;
	int 						mapHeigth;
	double					radius;
	double					posX;
	double					posY;
	double					spaceInterRadius;
	int							fisheyes;
	t_image					minimap;
	t_image					screen;
	t_intersection	inter[WIN_X];
	t_image					wall[4];
	long double			hpp; //hauteur par pixel;
	int							minimapX;
	int							minimapY;
	t_minimap				mm_info;
	int							error;
}									t_wolf;

int								ft_init(t_wolf *wolf, char **av);
void 							ft_free(t_wolf *wolf);
void 							ft_error(int error);
void							ft_wolf(t_wolf *wolf);

void 							init_textures(t_wolf *wolf);

int 							ft_fill_tab(t_wolf *wolf, char **av);
int								ft_display_hook(int keycode, void *mlx);
int								ft_redcross(t_wolf *wolf);
void							ft_pixel_put(t_image *img, int x, int y, int color);
void 							ft_draw_rectangle(t_point map0, t_point map1, t_image	*img,
									int color);
void							ft_line(t_point map0, t_point map1, t_image *img, int color);
t_point 					endpoint(double angle, int x1 , int y1, double lenght);
t_dpoint 					endpoint2(double angle, double x1 , double y1, double lenght);

double						d_cos(double degree);
double						d_sin(double degree);
double						d_tan(double degree);

t_dpoint 					find_dist(double angle);
t_dpoint 					find_first_dist(double posX, double posY, double angle);
t_intersection 		search_intersection(t_wolf *wolf, t_intersection inter);
void  						search_intersections(t_wolf *wolf);

void 							ft_search_intersections(t_wolf *wolf);

void							display_minimap(t_wolf *wolf);
void 							minimap_draw_angle(t_wolf *wolf);
void 							minimap_draw_map(t_wolf *wolf);
void 							minimap_draw_cadriage(t_wolf *wolf);
void 							minimap_draw_perso(t_wolf *wolf);

void 							init_screen(t_wolf *wolf);
void							display_screen(t_wolf *wolf);

void	ft_line_wall(t_point map0, t_point map1, t_image *img, int color);


#endif
