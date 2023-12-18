/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:47:40 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/18 01:54:15 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_line_dda(t_data *data, double x1, double y1, double x2, double y2, int color)
{
    data->line.diff_x = x2 - x1;
    data->line.diff_y = y2 - y1;
    data->line.steps = my_own_abs(data->line.diff_x) > my_own_abs(data->line.diff_y) ? my_own_abs(data->line.diff_x) : my_own_abs(data->line.diff_y);
    data->line.x_increment = (float)(data->line.diff_x) / (float)(data->line.steps);
    data->line.y_increment = (float)data->line.diff_y / (float)data->line.steps;
    data->line.x = (float)x1;
    data->line.y = (float)y1;
    my_mlx_pixel_put(data, my_own_round(data->line.x), my_own_round(data->line.y), color);
    while (data->line.steps > 0)
    {
        data->line.x += data->line.x_increment;
        data->line.y += data->line.y_increment;
        // printf("X = %d\n",  my_own_round(data->line.x));
        // printf("Y = %d\n",  my_own_round(data->line.y));
        my_mlx_pixel_put(data, my_own_round(data->line.x), my_own_round(data->line.y), color);
        data->line.steps--;
    }
}

int handle_keypress(int keycode, t_data *data)
{
    if (keycode == 123)
    {
        data->player.turn_direction = -1;
        // printf("rotation angle 9bl -> %f\n", data->player.rotation_angle);
        data->player.rotation_angle += data->player.turn_direction * data->player.rotation_speed;
        // printf("dkhlt l LEFT -> %f\n", data->player.rotation_angle);
        printf("new position: %f\n", data->player.x + (cos(data->player.rotation_angle) * 30));
    }
    else if (keycode == 124)
    {
        data->player.turn_direction = 1;
        // printf("rotation angle 9bl -> %f\n", data->player.rotation_angle);
        data->player.rotation_angle += data->player.turn_direction * data->player.rotation_speed;
        // printf("dkhlt l RIGHT -> %f\n", data->player.rotation_angle);
        // printf("old position: %f\n", data->player.x);
        printf("new position: %f\n", data->player.x + (cos(data->player.rotation_angle) * 30));
    }
    else if (keycode == 125)
    {
        data->player.walk_direction = -1;
        data->player.move_step += data->player.walk_direction * data->player.speed;
        data->player.x += cos(data->player.rotation_angle) * (data->player.move_step);
        data->player.y +=  data->player.y + sin(data->player.rotation_angle) * (data->player.move_step);
        printf("MOVE STEP : %f\n", data->player.move_step);
    }
    else if (keycode == 126)
    {
        data->player.walk_direction = 1;
        data->player.move_step += data->player.walk_direction * data->player.speed;
        data->player.x += cos(data->player.rotation_angle) * (data->player.move_step);
        data->player.y +=  data->player.y + sin(data->player.rotation_angle) * (data->player.move_step);
        printf("MOVE STEP : %f\n", data->player.move_step);
    }

    return (0);
}

int handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == 123 || keycode == 124)
        data->player.turn_direction = 0;
    else if (keycode == 125 || keycode == 126)
        data->player.walk_direction = 0;
    return (0);
}

void draw_scene(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < NUM_ROWS)
    {
        j = 0;
        while (j < NUM_COLS)
        {
            data->tile.tile_x = j * TILE_SIZE;
            data->tile.tile_y = i * TILE_SIZE;
            data->tile.tile_color = (data->map[i][j] == '1' ? 0x000066 : 0x0);
            if (data->map[i][j] == 'S')
            {
                draw_rect(data, data->tile.tile_x, data->tile.tile_y, TILE_SIZE, TILE_SIZE, 0x0);
                draw_rect(data, data->player.x, data->player.y, TILE_SIZE / 3, TILE_SIZE / 3, 0xFFFFFF);
            }
            else
                draw_rect(data, data->tile.tile_x, data->tile.tile_y, TILE_SIZE, TILE_SIZE, data->tile.tile_color);
            j++;
        }
        i++;
    }
}

int update_render(t_data *data)
{
    mlx_clear_window(data->mlx, data->mlx_new_window);
    draw_scene(data);
    // draw_line_dda (data,  data->player.x, data->player.y, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2), 0xff0111);
//     draw_rect(data, ,
//    ,TILE_SIZE / 3, TILE_SIZE / 3 , 0xffffff);
    draw_line_dda(data, data->player.x, data->player.y, data->player.x + cos(data->player.rotation_angle) * 30, data->player.y + sin(data->player.rotation_angle) * 30, 0xfffff);
    mlx_put_image_to_window(data->mlx, data->mlx_new_window, data->img_ptr, 0, 0);
    return (0);
}

int main()
{
    t_data data;
    char map[11][15] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
        {'1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', 'S', '0', '0', '0', '1', '0', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
    };

    data.player = (t_player){.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .move_step = 0, .speed = 1.5, .turn_direction = 0, .walk_direction = 0, .rotation_angle = PI / 2, .rotation_speed = 5 * (PI / 180)};
    data.mlx = mlx_init();
    data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "USM4");
    data.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.size_line, &data.endian);
    cpy_map(&data, map);
    if (!mlx_hook(data.mlx_new_window, 2, 0L, handle_keypress, &data))
        return ((perror("mlx hook failure")), 1);
    if (!mlx_hook(data.mlx_new_window, 3, 0, handle_keyrelease, &data))
        return ((perror("mlx hook failure")), 1);
    mlx_loop_hook(data.mlx, update_render, &data);
    mlx_loop(data.mlx);
}