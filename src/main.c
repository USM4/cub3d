/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/25 22:36:59 by  oredoine         ###   ########.fr       */
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
    if (keycode == 53)
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
                draw_rect(data, data->player.x, data->player.y, TILE_SIZE / 3, TILE_SIZE / 3, 0xffffff);
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
    // printf("i : %d\n", i);nngle
    // printf("map: %c\n", data->map[i][j]);
    if (i < 0 || i >= NUM_ROWS || j < 0 || j >= NUM_COLS || data->map[i][j] == '1')
        return (1);
    return (0);
}

void horizontal(t_data *data)
{
    // find the y coordinate of the closest horizontal tile
    data->ray.hit.next_hx = 0;
    data->ray.hit.next_hy = 0;

    data->ray.hit.y_point = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    data->ray.hit.y_point += data->ray.facing_down ? TILE_SIZE : 0;
    // find the x coordinate
    data->ray.hit.x_point = data->player.x + ((data->ray.hit.y_point - data->player.y) / tan(data->ray.ray_angle));
    // calculate the increment steps
    data->ray.hit.y_step = TILE_SIZE;
    data->ray.hit.y_step *= data->ray.facing_up ? -1 : 1;

    data->ray.hit.x_step = TILE_SIZE / tan(data->ray.ray_angle);
    data->ray.hit.x_step *= (data->ray.facing_left && data->ray.hit.x_step > 0) ? -1 : 1;
    data->ray.hit.x_step *= (data->ray.facing_right && data->ray.hit.x_step < 0) ? -1 : 1;
    data->ray.hit.next_hx = data->ray.hit.x_point;
    data->ray.hit.next_hy = data->ray.hit.y_point;

    int var = 0;
    // increment xStep and yStep unitil find the wall
    while (data->ray.hit.next_hx >= 0 && data->ray.hit.next_hx <= WINDOW_WIDTH && data->ray.hit.next_hy >= 0 && data->ray.hit.next_hy <= WINDOW_WIDTH)
    {
        if (data->ray.facing_up == 1)
            var = 1;
        else
            var = 0;
        if (check_is_wall(data->ray.hit.next_hx, data->ray.hit.next_hy - var, data))
        {
            data->ray.horz_wallhit_x = data->ray.hit.next_hx;
            data->ray.horz_wallhit_y = data->ray.hit.next_hy;
            draw_line_dda(data, data->player.x, data->player.y, data->ray.horz_wallhit_x, data->ray.horz_wallhit_y, 0xfffff);
            break;
        }
        else
        {
            data->ray.hit.next_hx += data->ray.hit.x_step;
            data->ray.hit.next_hy += data->ray.hit.y_step;
        }
    }
}

void vertical(t_data *data)
{
    // find the x coordinate of the closest horizontal tile
    data->ray.hit.next_vx = 0;
    data->ray.hit.next_vy = 0;

    data->ray.hit.x_point = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    data->ray.hit.x_point += data->ray.facing_right ? TILE_SIZE : 0;
    // find the y coordinate
    data->ray.hit.y_point = data->player.y + ((data->ray.hit.x_point - data->player.x) * tan(data->ray.ray_angle));
    // calculate the increment steps
    data->ray.hit.x_step = TILE_SIZE;
    data->ray.hit.x_step *= data->ray.facing_left ? -1 : 1;

    data->ray.hit.y_step = TILE_SIZE * tan(data->ray.ray_angle);
    data->ray.hit.y_step *= (data->ray.facing_up && data->ray.hit.y_step > 0) ? -1 : 1;
    data->ray.hit.y_step *= (data->ray.facing_down && data->ray.hit.y_step < 0) ? -1 : 1;

    data->ray.hit.next_vx = data->ray.hit.x_point;
    data->ray.hit.next_vy = data->ray.hit.y_point;

    int var = 0;
    // increment xStep and yStep unitil find the wall
    while (data->ray.hit.next_vx >= 0 && data->ray.hit.next_vx <= WINDOW_WIDTH && data->ray.hit.next_vy >= 0 && data->ray.hit.next_vy <= WINDOW_WIDTH)
    {
        if (data->ray.facing_left == 1)
            var = 1;
        else
            var = 0;
        if (check_is_wall(data->ray.hit.next_vx - var, data->ray.hit.next_vy, data))
        {
            data->ray.vert_wallhit_x = data->ray.hit.next_vx;
            data->ray.vert_wallhit_y = data->ray.hit.next_vy;
            draw_line_dda(data, data->player.x, data->player.y, data->ray.vert_wallhit_x, data->ray.vert_wallhit_y, 0xfffff);
            break;
        }
        else
        {
            data->ray.hit.next_vx += data->ray.hit.x_step;
            data->ray.hit.next_vy += data->ray.hit.y_step;
        }
    }
}

void distance_normalizing(t_data *data)
{
    
}

void update_position(t_data *data)
{
    // printf("move step fdkhla dl update %f = \n" ,data->player.move_step);
    data->player.rotation_angle += data->player.turn_direction * data->player.rotation_speed;
    if (!check_is_wall((data->player.x + cos(data->player.rotation_angle) * (data->player.move_step)),
                       data->player.y + (sin(data->player.rotation_angle) * (data->player.move_step)), data))
    {
        data->player.move_step += data->player.walk_direction * data->player.speed;
        data->player.x += cos(data->player.rotation_angle) * (data->player.move_step);
        data->player.y += sin(data->player.rotation_angle) * (data->player.move_step);
        data->ray.ray_angle = data->player.rotation_angle - (FOV / 2);
    }
}

void facing_normalization(t_data *data)
{

    data->ray.facing_right = 0;
    data->ray.facing_left = 0;
    data->ray.facing_up = 0;
    data->ray.facing_down = 0;

    if (data->player.rotation_angle > 0 && data->player.rotation_angle < PI)
        data->ray.facing_down = 1;
    else
        data->ray.facing_up = 1;

    if (data->player.rotation_angle < 0.5 * PI || data->player.rotation_angle > 1.5 * PI)
        data->ray.facing_right = 1;
    else
        data->ray.facing_left = 1;
    // printf("is ray facing right :: \n %d", data->ray.facing_right);
    printf("ray angle %f\n", data->player.rotation_angle);
}

double nornmalize_any_angle(double angle)
{
    if (angle < 0)
        angle += (2 * PI);
    else if (angle > 2 * PI)
        angle = fmod(angle, 2 * PI);
    return (angle);
}

int update_render(t_data *data)
{
    mlx_clear_window(data->mlx, data->mlx_new_window);
    update_position(data);
    draw_scene(data);
    draw_player(data);
    // draw_rect(data, data->player.x , data->player.y ,TILE_SIZE / 3, TILE_SIZE / 3 , 0xffffff);
    // draw_line_dda(data, data->player.x, data->player.y, data->player.x + cos(data->player.rotation_angle) * 30, data->player.y + sin(data->player.rotation_angle) * 30, 0xfffff);
    data->ray.ray_angle = nornmalize_any_angle(data->ray.ray_angle);
    data->player.rotation_angle = nornmalize_any_angle(data->player.rotation_angle);
    facing_normalization(data);
    horizontal(data);
    vertical(data);
    // draw_line_dda(data, data->player.x, data->player.y, data->player.x + cos(data->ray.ray_angle) * 30, data->player.y + sin(data->ray.ray_angle) * 30, 0xfffff);
    printf("facing up %d\n", data->ray.facing_up);
    printf("facing DOWN %d\n", data->ray.facing_down);
    printf("facing RIGHT %d\n", data->ray.facing_right);
    printf("facing  LEFT %d\n", data->ray.facing_left);
    mlx_put_image_to_window(data->mlx, data->mlx_new_window, data->img_ptr, 0, 0);
    return (0);
}

// void cast_single_ray(t_data *data)
// {

// }

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
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
    data.player = (t_player){.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .move_step = 0, .speed = 0.2, .turn_direction = 0, .walk_direction = 0, .rotation_angle = PI, .rotation_speed = 3 * (PI / 180)};
    data.ray = (t_ray){.horz_wallhit_x = 0, .horz_wallhit_y = 0, .vert_wallhit_x = 0, .vert_wallhit_y = 0, .distance = 0, .ray_angle = PI / 2, .facing_down = 0, .facing_up = 0, .facing_left = 0, .facing_right = 0};
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