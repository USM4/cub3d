/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:47:40 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/21 03:49:27 by oredoine         ###   ########.fr       */
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
        data->player.turn_direction = -1;
    if (keycode == 124)
        data->player.turn_direction = 1;
    if (keycode == 125)
        data->player.walk_direction = -1;
    if (keycode == 126)
        data->player.walk_direction = 1;
    if(keycode == 53)
        exit(0);

    return (0);
}

int handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == 123 || keycode == 124)
        data->player.turn_direction = 0;
    if (keycode == 125 || keycode == 126)
    {
        data->player.walk_direction = 0;
        data->player.move_step = 0;
    }
    return (0);
}
void draw_player(t_data *data)
{
    int i;
    int j;
    i = 0;
    while (i < NUM_ROWS)
    {
        j = 0;
        while (j < NUM_COLS)
        {
            if (data->map[i][j] == 'S')
                draw_rect(data, data->player.x, data->player.y,  TILE_SIZE / 3, TILE_SIZE / 3, 0xffffff);
            j++;
        }
        i++;
    }
    
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
            draw_rect(data, data->tile.tile_x, data->tile.tile_y, TILE_SIZE, TILE_SIZE, data->tile.tile_color);
            j++;
        }
        i++;
    }
}

int check_is_wall(double x, double y, t_data *data)
{
    int i;
    int j;
    x /= TILE_SIZE;
    y /= TILE_SIZE;
    i = floor(y);
    // printf("x : %f\n", x);
    j = floor(x);
    // printf("j : %d\n", j);
    // printf("i : %d\n", i);
    // printf("map: %c\n", data->map[i][j]);
    if(i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS ||  data->map[i][j] == '1')
        return(1);
    return(0);
}

void update_position(t_data *data)
{
    printf("move step fdkhla dl update %f = \n" ,data->player.move_step);
    data->player.rotation_angle += data->player.turn_direction * data->player.rotation_speed;
    if(!check_is_wall((data->player.x + cos(data->player.rotation_angle) * (data->player.move_step)), \
    data->player.y + (sin(data->player.rotation_angle) * (data->player.move_step)) , data))
    {
        data->player.move_step += data->player.walk_direction * data->player.speed;
        data->player.x += cos(data->player.rotation_angle) * (data->player.move_step);
        data->player.y += sin(data->player.rotation_angle) * (data->player.move_step);
    }
}

void single_ray(double ray_angle, int id)
{
    
}

void raycasting(t_data *data)
{
    double ray_angle;
    int id;
    ray_angle = data->player.rotation_angle - (FOV / 2);
    id = 0;
    while (id  < NUM_RAYS)
    {
        single_ray(ray_angle, id);
        ray_angle += FOV / NUM_RAYS;
        id++;
    }
    
}

int update_render(t_data *data)
{
    update_position(data);
    mlx_clear_window(data->mlx, data->mlx_new_window);
    draw_scene(data);
    draw_player(data);
    // draw_rect(data, data->player.x , data->player.y ,TILE_SIZE / 3, TILE_SIZE / 3 , 0xffffff);
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

    data.player = (t_player){.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .move_step = 0, .speed = 0.2, .turn_direction = 0, .walk_direction = 0, .rotation_angle = PI , .rotation_speed = 3 * (PI / 180)};
    data.mlx = mlx_init();
    // printf("player x %f\n", data.player.x);
    // printf("player y %f\n", data.player.y);
    data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "USM4");
    data.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.size_line, &data.endian);
    cpy_map(&data, map);
    draw_scene(&data);
    draw_player(&data);
    // draw_rect(&data, data.player.x , data.player.y ,TILE_SIZE / 3, TILE_SIZE / 3 , 0xffffff);
    draw_line_dda(&data, data.player.x, data.player.y, data.player.x + cos(data.player.rotation_angle) * 30, data.player.y + sin(data.player.rotation_angle) * 30, 0xfffff);
    
    if (!mlx_hook(data.mlx_new_window, 2, 0, handle_keypress, &data))
        return ((perror("mlx hook failure")), 1);
    if (!mlx_hook(data.mlx_new_window, 3, 0, handle_keyrelease, &data))
        return ((perror("mlx hook failure")), 1);
    mlx_loop_hook(data.mlx, update_render, &data);
    mlx_loop(data.mlx);
}