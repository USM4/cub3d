/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:28:08 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/12 14:16:13 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# define TILE_SIZE 64
# define NUM_ROWS 11
# define NUM_COLS 15
# define PI 3.14159265359
# define WINDOW_HEIGHT TILE_SIZE * NUM_ROWS
# define WINDOW_WIDTH TILE_SIZE * NUM_COLS
# define FOV 60 * (PI / 180)
# define NUM_RAYS WINDOW_WIDTH
# define FACTOR 0.2



typedef struct s_textures
{
	double		x;
	double		y;
	int			height;
	int			width;
	void		*n_img;
	void		*s_img;
	void		*e_img;
	void		*w_img;
	uint32_t	*arr;
}	t_textures;

typedef struct s_intersections
{
	double	x_point;
	double	y_point;
	double	x_step;
	double	y_step;
	double	next_hx;
	double	next_hy;
	double	next_vx;
	double	next_vy;

}	t_intersections;

typedef struct s_player
{
	double	x;
	double	y;
	double	speed;
	double	move_step;
	double	turn_direction;
	double	walk_direction;
	double	rotation_angle;
	double	rotation_speed;
	int		flag;
}	t_player;

typedef struct s_tile
{
	double	tile_x;
	double	tile_y;
	int		tile_color;
}	t_tile;

typedef struct s_ray
{
	double			ray_angle;
	double			horz_wallhit_x;
	double			horz_wallhit_y;
	double			vert_wallhit_x;
	double			vert_wallhit_y;
	double			distance;
	double			the_x_wallhit;
	double			the_y_wallhit;
	int				facing_down;
	int				facing_up;
	int				facing_right;
	int				facing_left;
	int				flag_v;
	int				flag_h;
	t_intersections	hit;
}	t_ray;

typedef struct s_dda
{
	double	x;
	double	y;
	double	diff_x;
	double	diff_y;
	double	steps;
	double	x_increment;
	double	y_increment;
}	t_dda;

typedef struct s_data
{
	char		**map;
	void		*mlx_new_window;
	void		*img_ptr;
	char		*addr_ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*mlx;
	t_player	player;
	t_tile		tile;
	t_dda		line;
	t_ray		ray[NUM_RAYS];
	t_textures	offset;
	t_textures	textures[4];
}	t_data;

extern void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
extern void		draw_rect(t_data *data, double x, double y, double width, \
double height, int color);
extern int		my_own_round(double num);
extern int		my_own_abs(int num);
extern void		cpy_map(t_data *data, char map[NUM_ROWS][NUM_COLS]);
extern void		horizontal(t_data *data, int i);
extern void		vertical(t_data *data, int i);
extern void		distance_normalizing(t_data *data, int i);
extern int		check_is_wall(double x, double y, t_data *data);
extern void		facing_normalization(t_ray *ray);
extern double	nornmalize_any_angle(double angle);
extern void		draw_all_lines(t_data *data, int i, double angle);
extern double	caculate_distance_of_two_point(double x2, double y2, \
double x1, double y1);
extern int		quit_window(void);
#endif