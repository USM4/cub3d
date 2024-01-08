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

#include <string.h>

void draw_line_dda(t_data *data, double x1, double y1, double x2, double y2, int color)
{
    data->line.diff_x = x2 - x1;
    data->line.diff_y = y2 - y1;
    if (my_own_abs(data->line.diff_x) > my_own_abs(data->line.diff_y))
        data->line.steps = my_own_abs(data->line.diff_x);
    else
        data->line.steps = my_own_abs(data->line.diff_y);

    data->line.x_increment = (float)(data->line.diff_x) / (float)(data->line.steps);
    data->line.y_increment = (float)data->line.diff_y / (float)data->line.steps;
    data->line.x = (float)x1;
    data->line.y = (float)y1;
    my_mlx_pixel_put(data, my_own_round(data->line.x), my_own_round(data->line.y), color);
    while (data->line.steps > 0)
    {
        data->line.x += data->line.x_increment;
        data->line.y += data->line.y_increment;
        my_mlx_pixel_put(data, my_own_round(data->line.x), my_own_round(data->line.y), color);
        data->line.steps--;
    }
}

int handle_keypress(int keycode, t_data *data)
{
    //arrows
    if (keycode == 123)
        data->player.turn_direction = -1;
    else if (keycode == 124)
        data->player.turn_direction = 1;

    // alphabets
    else if (keycode == 0)
    {
        // printf("A\n");
        data->player.flag = -1;
        // printf("flag A %f\n", data->player.flag);
        data->player.walk_direction = 1;
    }
    else if (keycode == 2)
    {
        // printf("D\n");
        data->player.flag = 1;
        data->player.walk_direction = 1;
        // printf("flag D %f\n", data->player.flag);
    }
    else if (keycode == 13)
        data->player.walk_direction = 1;
    else if (keycode == 1)
        data->player.walk_direction = -1;
    else if (keycode == 53)
        exit(0);
    return (0);
}

int handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == 123 || keycode == 124)
        data->player.turn_direction = 0;
    if (keycode == 13 ||  keycode == 1 )
    {
        data->player.walk_direction = 0;
        data->player.move_step = 0;
    }
    if ( keycode == 2 || keycode == 0)
    {
        data->player.flag = 0;
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
                draw_rect(data, FACTOR * data->player.x, FACTOR * data->player.y, FACTOR * (TILE_SIZE / 3), FACTOR * (TILE_SIZE / 3), 0xfcdb03);
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
            if (data->map[i][j] == '1')
                data->tile.tile_color = 0x000066;
            else
                data->tile.tile_color = 0x0;
            draw_rect(data, FACTOR * data->tile.tile_x, FACTOR * data->tile.tile_y, FACTOR * TILE_SIZE, FACTOR * TILE_SIZE, data->tile.tile_color);
            j++;
        }
        i++;
    }
}

int check_is_wall_rc(double x, double y, t_data *data)
{
    int i;
    int j;
    x /= TILE_SIZE;
    y /= TILE_SIZE;
    i = floor(y);
    j = floor(x);
    if (i <= 0 || i >= NUM_ROWS || j <= 0 || j >= NUM_COLS || data->map[i][j] == '1')
        return (1);
    return (0);
}
int check_is_wall_player(double x, double y, t_data *data)
{
    int i;
    int j;

    x /= TILE_SIZE;
    y /= TILE_SIZE;
    i = floor(y);
    j = floor(x);
    if (i <= 0 || i >= NUM_ROWS || j <= 0 || j >= NUM_COLS || data->map[i][j] == '1')
        return (1);
    if(data->map[i][j] == '1' )
        return (1);
    return (0);
}

void horizontal(t_data *data, int i)
{
        int decrement;

    // find the y coordinate of the closest horizontal tile
    decrement = 0;
    data->ray[i].hit.next_hx = 0;
    data->ray[i].hit.next_hy = 0;

    data->ray[i].hit.y_point = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    if (data->ray[i].facing_down == 1)
        data->ray[i].hit.y_point += TILE_SIZE;
    // find the x coordinate
    data->ray[i].hit.x_point = data->player.x + (data->ray[i].hit.y_point - data->player.y) / tan(data->ray[i].ray_angle);
    // calculate the increment steps
    data->ray[i].hit.y_step = TILE_SIZE;
    if (data->ray[i].facing_up == 1)
        data->ray[i].hit.y_step *= -1;
    data->ray[i].hit.x_step = TILE_SIZE / tan(data->ray[i].ray_angle);
    if ((data->ray[i].facing_left && data->ray[i].hit.x_step > 0))
        data->ray[i].hit.x_step *= -1;
    if (data->ray[i].facing_right && data->ray[i].hit.x_step < 0)
        data->ray[i].hit.x_step *= -1;
    data->ray[i].hit.next_hx = data->ray[i].hit.x_point;
    data->ray[i].hit.next_hy = data->ray[i].hit.y_point;
    // increment xStep and yStep unitil find the wall

    while (data->ray[i].hit.next_hx >= 0 && data->ray[i].hit.next_hx <= WINDOW_WIDTH && data->ray[i].hit.next_hy >= 0 && data->ray[i].hit.next_hy <= WINDOW_HEIGHT)
    {
        if (data->ray[i].facing_up == 1)
            decrement = 1;
        else
            decrement = 0;
        if (check_is_wall_rc(data->ray[i].hit.next_hx, data->ray[i].hit.next_hy - decrement, data))
        {
            data->ray[i].horz_wallhit_x = data->ray[i].hit.next_hx;
            data->ray[i].horz_wallhit_y = data->ray[i].hit.next_hy;
            break;
        }
        else
        {
            data->ray[i].hit.next_hx += data->ray[i].hit.x_step;
            data->ray[i].hit.next_hy += data->ray[i].hit.y_step;
        }
    }
    data->ray[i].horz_wallhit_x = data->ray[i].hit.next_hx;
    data->ray[i].horz_wallhit_y = data->ray[i].hit.next_hy;
}

void vertical(t_data *data, int i)
{
    int var;
    // find the x coordinate of the closest horizontal tile

    var = 0;
    data->ray[i].hit.next_vx = 0;
    data->ray[i].hit.next_vy = 0;

    data->ray[i].hit.x_point = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    if (data->ray[i].facing_right == 1)
        data->ray[i].hit.x_point += TILE_SIZE;
    // find the y coordinate
    data->ray[i].hit.y_point = data->player.y + (data->ray[i].hit.x_point - data->player.x) * tan(data->ray[i].ray_angle);
    // calculate the increment steps
    data->ray[i].hit.x_step = TILE_SIZE;
    if (data->ray[i].facing_left)
        data->ray[i].hit.x_step *= -1;
    data->ray[i].hit.y_step = TILE_SIZE * tan(data->ray[i].ray_angle);

    if ((data->ray[i].facing_up && data->ray[i].hit.y_step > 0))
        data->ray[i].hit.y_step *= -1;
    else
        data->ray[i].hit.y_step *= 1;

    if ((data->ray[i].facing_down && data->ray[i].hit.y_step < 0))
        data->ray[i].hit.y_step *= -1;
    else
        data->ray[i].hit.y_step *= 1;
    data->ray[i].hit.next_vx = data->ray[i].hit.x_point;
    data->ray[i].hit.next_vy = data->ray[i].hit.y_point;
    // increment xStep and yStep unitil find the wall
    while ((data->ray[i].hit.next_vx >= 0 && data->ray[i].hit.next_vx <= WINDOW_WIDTH) && (data->ray[i].hit.next_vy >= 0 && data->ray[i].hit.next_vy <= WINDOW_HEIGHT))
    {
        if (data->ray[i].facing_left == 1)
            var = 1;
        else
            var = 0;
        if (check_is_wall_rc(data->ray[i].hit.next_vx - var, data->ray[i].hit.next_vy, data))
        {
            data->ray[i].vert_wallhit_x = data->ray[i].hit.next_vx;
            data->ray[i].vert_wallhit_y = data->ray[i].hit.next_vy;
            break;
        }
        else
        {
            data->ray[i].hit.next_vx += data->ray[i].hit.x_step;
            data->ray[i].hit.next_vy += data->ray[i].hit.y_step;
        }
    }
    data->ray[i].vert_wallhit_x = data->ray[i].hit.next_vx;
    data->ray[i].vert_wallhit_y = data->ray[i].hit.next_vy;
}

void update_position(t_data *data)
{
    double new_x;
    double new_y;
    double angle;

    data->player.rotation_angle += data->player.turn_direction * data->player.rotation_speed;
    angle = data->player.rotation_angle + (data->player.flag * (PI / 2));
    new_x = data->player.x + cos(angle) * (data->player.move_step);
    new_y = data->player.y + sin(angle) * (data->player.move_step);
    if (!check_is_wall_player(new_x + 10, new_y, data) 
    &&  !check_is_wall_player(new_x - 10, new_y, data) 
    && !check_is_wall_player(new_x, new_y + 10, data) 
    && !check_is_wall_player(new_x, new_y - 10, data))
    {
        data->player.move_step += data->player.walk_direction * data->player.speed;
        data->player.x = new_x;
        data->player.y = new_y;
    }
}

void facing_normalization(t_ray *ray)
{
    ray->facing_right = 0;
    ray->facing_left = 0;
    ray->facing_up = 0;
    ray->facing_down = 0;

    if (ray->ray_angle > 0 && ray->ray_angle < PI)
        ray->facing_down = 1;
    else
        ray->facing_up = 1;

    if (ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI)
        ray->facing_right = 1;
    else
        ray->facing_left = 1;
}

double nornmalize_any_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

double caculate_distance_of_two_point(double x2, double y2, double x1, double y1)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void distance_normalizing(t_data *data, int i)
{
    double horz_distance;
    double ver_distance;

    horz_distance = caculate_distance_of_two_point(data->ray[i].horz_wallhit_x, data->ray[i].horz_wallhit_y,
                                                   data->player.x, data->player.y);
    ver_distance = caculate_distance_of_two_point(data->ray[i].vert_wallhit_x, data->ray[i].vert_wallhit_y,
                                                  data->player.x, data->player.y);
    // if (horz_distance == 0)
    //     printf("%f\n", horz_distance);
    // if (ver_distance == 0)
    //     printf("%f\n", horz_distance);

    if (horz_distance > ver_distance)
    {
        data->ray[i].the_x_wallhit = data->ray[i].vert_wallhit_x;
        data->ray[i].the_y_wallhit = data->ray[i].vert_wallhit_y;
        data->ray[i].distance = ver_distance;
    }
    else
    {
        data->ray[i].the_x_wallhit = data->ray[i].horz_wallhit_x;
        data->ray[i].the_y_wallhit = data->ray[i].horz_wallhit_y;
        data->ray[i].distance = horz_distance;
    }
}

void draw_all_lines(t_data *data, int i, double angle)
{
    // data->player.rotation_angle = nornmalize_any_angle(data->player.rotation_angle);
    // data->ray[i].ray_angle = nornmalize_any_angle(data->ray[i].ray_angle);
    data->ray[i].ray_angle = angle;
    facing_normalization(&data->ray[i]);
    horizontal(data, i);
    vertical(data, i);
    distance_normalizing(data, i);
    // draw_line_dda(data, FACTOR * data->player.x, FACTOR * data->player.y, FACTOR * data->ray[i].the_x_wallhit, FACTOR * data->ray[i].the_y_wallhit, 0xfffff);
}

void render_3d(t_data *data)
{
    int i;
    double distance_prj_plane;
    double wall_stripe_height;
    double fish_bowl;

    i = 0;
    while (i < NUM_RAYS)
    {
        fish_bowl = data->ray[i].distance * cos(data->ray[i].ray_angle - data->player.rotation_angle);
        distance_prj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        wall_stripe_height = (TILE_SIZE / fish_bowl) * distance_prj_plane;
        // int y = 0;
        // while (y < ((WINDOW_HEIGHT) / 2) - (wall_stripe_height / 2))
        // {
        //     my_mlx_pixel_put(data, i, y, 0xFFFFFF);
        //     y++;
        // }
        if (wall_stripe_height > WINDOW_HEIGHT * 2)
            wall_stripe_height = WINDOW_HEIGHT * 2;
        draw_rect(data, i, ((WINDOW_HEIGHT) / 2) - (wall_stripe_height / 2), 1, wall_stripe_height, 0x0);
        i++;
    }
}

int update_render(t_data *data)
{
    int i;
    double angle;
    double angle_increment;

    i = 0;
    mlx_clear_window(data->mlx, data->mlx_new_window);
    update_position(data);
    data->player.rotation_angle = nornmalize_any_angle(data->player.rotation_angle);
    angle_increment = (FOV) / (NUM_RAYS);
    angle = data->player.rotation_angle - ((FOV) / 2);
    draw_rect(data, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xfc6500);
    render_3d(data);
    while (i < (NUM_RAYS))
    {
        // bzero(&data->ray[i], sizeof(t_ray));
        data->ray[i] = (t_ray) {.the_x_wallhit = 0, .the_y_wallhit = 0, .horz_wallhit_x = 0, .horz_wallhit_y = 0, .vert_wallhit_x = 0, .vert_wallhit_y = 0, .distance = 0, .ray_angle = PI / 2, .facing_down = 0, .facing_up = 0, .facing_left = 0, .facing_right = 0};
        draw_all_lines(data, i, nornmalize_any_angle(angle));
        angle += angle_increment;
        i++;
    }
    draw_scene(data);
    draw_player(data);
    i = 0;
    while (i < NUM_RAYS)
    {
        draw_line_dda(data, FACTOR * data->player.x, FACTOR * data->player.y, FACTOR * data->ray[i].the_x_wallhit, FACTOR * data->ray[i].the_y_wallhit, 0xfc6500);
        i++;
    }
    draw_line_dda(data, FACTOR * (data->player.x), FACTOR * (data->player.y), FACTOR * (data->player.x + cos(data->player.rotation_angle) * 30), FACTOR * (data->player.y + sin(data->player.rotation_angle) * 30), 0xfcdb03);
    mlx_put_image_to_window(data->mlx, data->mlx_new_window, data->img_ptr, 0, 0);
    return (0);
}

int main()
{
    t_data data;
    char map[11][15] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', 'S', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
    data.player = (t_player){.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .move_step = 0, .speed = 0.2, .turn_direction = 0, .walk_direction = 0, .flag = 0 , .rotation_angle = PI, .rotation_speed = 2 * (PI / 180)};
    data.mlx = mlx_init();
    data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "USM4");
    data.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.size_line, &data.endian);
    cpy_map(&data, map);
    if (!mlx_hook(data.mlx_new_window, 2, 0, handle_keypress, &data))
        return ((perror("mlx hook failure")), 1);
    if (!mlx_hook(data.mlx_new_window, 3, 0, handle_keyrelease, &data))
        return ((perror("mlx hook failure")), 1);
    if (!mlx_hook(data.mlx_new_window, 17, 0, quit_window, &data))
        return ((perror("mlx hook failure")), 1);
    mlx_loop_hook(data.mlx, update_render, &data);
    mlx_loop(data.mlx);
}