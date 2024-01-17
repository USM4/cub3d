/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:28:08 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/17 04:03:49 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include "parsing.h"
# define TILE_SIZE 64 //!!
# define PI 3.14159265359
# define FACTOR 0.2

typedef struct s_draw
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
}	t_draw;

typedef struct s_textures
{
	double		x;
	double		y;
	int			height;
	int			width;
	int			id;
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

typedef struct s_utils
{
	int		window_height;
	int		window_width;
	double	fov;
}	t_utils;

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
	t_ray		*ray;
	t_textures	offset;
	t_textures	textures[4];
	t_draw		params;
	t_elements	bridge;
	t_utils		val;
}	t_data;

extern void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
extern void		draw_rect(t_data *data);
extern int		my_own_round(double num);
extern int		my_own_abs(int num);
extern void		cpy_map(t_data *data, char **map);
extern void		horizontal(t_data *data, int i);
extern void		vertical(t_data *data, int i);
extern void		distance_normalizing(t_data *data, int i);
extern int		check_is_wall(double x, double y, t_data *data);
extern void		facing_normalization(t_ray *ray);
extern double	nornmalize_any_angle(double angle);
extern void		draw_all_lines(t_data *data, int i, double angle);
extern double	caculate_distance_of_two_point(double x2, double y2,
					double x1, double y1);
extern int		quit_window(void);
extern void		render_textures(t_data *data, int i, double wall_stripe_height,
					double wallheight);
extern double	calculate_wall_dementions(t_data *data, int i);
extern void		render_3d(t_data *data);
extern void		select_texture(t_data *data, int i);
extern void		loop_for_hz_intersection(t_data *data, int i);
extern void		horizontal(t_data *data, int i);
extern void		vertical(t_data *data, int i);
extern int		handle_keypress(int keycode, t_data *data);
extern void		draw_player(t_data *data);
extern void		draw_scene(t_data *data);
extern void		update_position(t_data *data);
extern int		handle_keyrelease(int keycode, t_data *data);
extern void		update_game_state(t_data *data);
extern void		render_game(t_data *data);
extern int		update_render(t_data *data);
extern void		draw_line_dda(t_data *data, double x1, double y1,
					double x2, double y2, int color);
extern void		initialize_mlx_ingredients2(t_data *data);
extern void		initialize_my_structs(t_data *data);
extern int		num_rows_counter(char **map);
extern void		initialize_player_position(t_data *data);
extern void		initialize_player_facing(t_data *data);
extern void		handle_textures_failing(t_data *data);
extern void		mlx_failure_protection(t_data *data);
#endif