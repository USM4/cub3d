/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:28:08 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/18 01:22:19 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <unistd.h>

#define TILE_SIZE 32
#define NUM_ROWS 11
#define NUM_COLS 15
#define PI 3.14159265359


#define WINDOW_HEIGHT TILE_SIZE * NUM_ROWS
#define WINDOW_WIDTH TILE_SIZE * NUM_COLS

typedef struct s_player
{
    double x;
    double y;
    double speed;
    double move_step;
    int turn_direction;
    int walk_direction;
    double  rotation_angle;
    double  rotation_speed;
} t_player;

typedef struct s_tile
{
    double tile_x;
    double tile_y;
    int tile_color;
} t_tile;

typedef struct s_dda
{
    double      x;
    double      y;
    double      diff_x;
    double      diff_y;
    double      steps;
    double      x_increment;
    double      y_increment;
}   t_dda;

typedef struct s_data
{
    char **map;
    void *mlx_new_window;
    void *img_ptr;
    char *addr_ptr;
    int bits_per_pixel;
    int size_line;
    int endian;
    void *mlx;
    t_player player;
    t_tile tile;
    t_dda  line; 
} t_data;

extern void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
extern void    draw_rect(t_data *data, int x, int y, int width, int height, int color);
extern int     my_own_round(float num);
extern int     my_own_abs(int num);
extern void    cpy_map(t_data *data, char map[NUM_ROWS][NUM_COLS]);



#endif