/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:47:40 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/09 01:36:17 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void draw_rect(t_data *data, int x, int y, int width, int height, int color)
{
    int i;
    int j;

    i = x;
    while (i < x + width)
    {
        j = y;
        while (j < y + height)
        {
            mlx_pixel_put(data->mlx, data->mlx_new_window, i, j, color);
            j++;
        }
        i++;
    }
}

int main ()
{
    int i = 0;
    int j; 
    t_data data;
    int map[][15] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    int tile_x;
    int tile_y;
    int tile_color;
    data.mlx = mlx_init();
    data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "USM4");
    while (i < NUM_ROWS)
    {
        j = 0;
        while (j < NUM_COLS)
        {
            tile_x = j * TILE_SIZE;
            tile_y = i * TILE_SIZE;
            tile_color = map[i][j] == 1 ? 0x000000 : 0xFFFFFF;
	        draw_rect(&data, tile_x, tile_y, WINDOW_WIDTH, WINDOW_HEIGHT, tile_color);
            j++;
        }  
        printf("\n");
        i++;
    }
    mlx_loop(data.mlx);
}  