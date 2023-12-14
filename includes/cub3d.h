/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:28:08 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/14 01:34:44 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <mlx.h>
#include <unistd.h>

#define TILE_SIZE 32
#define NUM_ROWS 11
#define NUM_COLS 15
#define PI 3.14159265359

#define WINDOW_HEIGHT TILE_SIZE * NUM_ROWS
#define WINDOW_WIDTH TILE_SIZE * NUM_COLS

typedef struct s_player
{
    int x;
    int y;
    float speed;
    int turn_direction;
    int walk_direction;
    int rotation_angle;
    int rotation_speed;
} t_player;

typedef struct s_tile
{
    int tile_x;
    int tile_y;
    int tile_color;
} t_tile;

typedef struct s_data
{
    void *mlx_new_window;
    void *img_ptr;
    char *addr_ptr;
    int bits_per_pixel;
    int size_line;
    int endian;
    void *mlx;
    t_player player;
    char map[11][15];
    t_tile tile;
} t_data;




#endif