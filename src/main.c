/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:47:40 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/12 19:18:56 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_ptr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_rect(t_data *data, int x, int y, int width, int height, int color)
{
    int i;
    int j;

    i = y;
    while (i < y + height)
    {
        j = x;
        while (j < x + width)
        {
            printf("gere x : %d - y : %d \n", j, i);
            my_mlx_pixel_put(data, j, i, color);
            j++;
        }
        i++;
    }
}

int main()
{
    t_data data;
    t_tile infos;
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
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    // t_player p = {.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .raduis = 3, .facing = BACK};
    data.mlx = mlx_init();
    data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "USM4");
    data.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.size_line, &data.endian);
    int i = 0;
    int j;
    while (i < NUM_ROWS)
    {
        j = 0;
        while (j < NUM_COLS)
        {
            infos.tile_x = j * TILE_SIZE;
            infos.tile_y = i * TILE_SIZE;
            infos.tile_color = map[i][j] == 1 ? 0x000066 : 0x0;
            if (i == 5 && j == 7)
            {
                infos.tile_color = 0xFFFFFF;
                draw_rect(&data, infos.tile_x, infos.tile_y, TILE_SIZE, TILE_SIZE, 0x0);
                draw_rect(&data, infos.tile_x + (TILE_SIZE / 3), infos.tile_y + (TILE_SIZE / 3), TILE_SIZE / 3, TILE_SIZE / 3, infos.tile_color);
            }
            else
                draw_rect(&data, infos.tile_x, infos.tile_y, TILE_SIZE, TILE_SIZE, infos.tile_color);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(data.mlx, data.mlx_new_window, data.img_ptr, 0, 0);
    mlx_loop(data.mlx);
}