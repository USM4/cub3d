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
                draw_rect(data, FACTOR * data->player.x, FACTOR * data->player.y, FACTOR * (TILE_SIZE / 3), FACTOR * (TILE_SIZE / 3), 0xffffff);
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
            draw_rect(data, FACTOR * data->tile.tile_x, FACTOR * data->tile.tile_y, FACTOR * TILE_SIZE, FACTOR * TILE_SIZE, data->tile.tile_color);
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
    if (i <= 0 || i >= NUM_ROWS || j <= 0 || j >= NUM_COLS || data->map[i][j] == '1')
        return (1);
    return (0);
}

void horizontal(t_data *data, int i)
{
    // find the y coordinate of the closest horizontal tile
    data->ray[i].hit.next_hx = 0;
    data->ray[i].hit.next_hy = 0;

    data->ray[i].hit.y_point = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    data->ray[i].hit.y_point += data->ray[i].facing_down ? TILE_SIZE : 0;
    // find the x coordinate
    data->ray[i].hit.x_point = data->player.x + ((data->ray[i].hit.y_point - data->player.y) / tan(data->ray[i].ray_angle));
    // calculate the increment steps
    data->ray[i].hit.y_step = TILE_SIZE;
    data->ray[i].hit.y_step *= data->ray[i].facing_up ? -1 : 1;

    data->ray[i].hit.x_step = TILE_SIZE / tan(data->ray[i].ray_angle);
    data->ray[i].hit.x_step *= (data->ray[i].facing_left && data->ray[i].hit.x_step > 0) ? -1 : 1;
    data->ray[i].hit.x_step *= (data->ray[i].facing_right && data->ray[i].hit.x_step < 0) ? -1 : 1;
    data->ray[i].hit.next_hx = data->ray[i].hit.x_point;
    data->ray[i].hit.next_hy = data->ray[i].hit.y_point;

    int decrement = 0;
    // increment xStep and yStep unitil find the wall

    while ((data->ray[i].hit.next_hx >= 0 && data->ray[i].hit.next_hx <= WINDOW_WIDTH) && (data->ray[i].hit.next_hy >= 0 && data->ray[i].hit.next_hy <= WINDOW_HEIGHT))
    {
        if (data->ray[i].facing_up == 1)
            decrement = 1;
        else
            decrement = 0;
        if (!check_is_wall(data->ray[i].hit.next_hx, data->ray[i].hit.next_hy - decrement, data))
        {
            data->ray[i].hit.next_hx += data->ray[i].hit.x_step;
            data->ray[i].hit.next_hy += data->ray[i].hit.y_step;
        }
        else
        {
            data->ray[i].horz_wallhit_x = data->ray[i].hit.next_hx;
            data->ray[i].horz_wallhit_y = data->ray[i].hit.next_hy;
            break;
        }
    }
}

void vertical(t_data *data, int i)
{
    // find the x coordinate of the closest horizontal tile
    data->ray[i].hit.next_vx = 0;
    data->ray[i].hit.next_vy = 0;

    data->ray[i].hit.x_point = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    data->ray[i].hit.x_point += data->ray[i].facing_right ? TILE_SIZE : 0;
    // find the y coordinate
    data->ray[i].hit.y_point = data->player.y + (data->ray[i].hit.x_point - data->player.x) * tan(data->ray[i].ray_angle);
    // calculate the increment steps
    data->ray[i].hit.x_step = TILE_SIZE;
    data->ray[i].hit.x_step *= data->ray[i].facing_left ? -1 : 1;

    data->ray[i].hit.y_step = TILE_SIZE * tan(data->ray[i].ray_angle);
    data->ray[i].hit.y_step *= (data->ray[i].facing_up && data->ray[i].hit.y_step > 0) ? -1 : 1;
    data->ray[i].hit.y_step *= (data->ray[i].facing_down && data->ray[i].hit.y_step < 0) ? -1 : 1;

    data->ray[i].hit.next_vx = data->ray[i].hit.x_point;
    data->ray[i].hit.next_vy = data->ray[i].hit.y_point;

    int var = 0;
    // increment xStep and yStep unitil find the wall
    while ((data->ray[i].hit.next_vx >= 0 && data->ray[i].hit.next_vx <= WINDOW_WIDTH) && (data->ray[i].hit.next_vy >= 0 && data->ray[i].hit.next_vy <= WINDOW_HEIGHT))
    {
        if (data->ray[i].facing_left == 1)
            var = 1;
        else
            var = 0;
        if (!check_is_wall(data->ray[i].hit.next_vx - var, data->ray[i].hit.next_vy, data))
        {
            data->ray[i].hit.next_vx += data->ray[i].hit.x_step;
            data->ray[i].hit.next_vy += data->ray[i].hit.y_step;
        }
        else
        {
            data->ray[i].vert_wallhit_x = data->ray[i].hit.next_vx;
            data->ray[i].vert_wallhit_y = data->ray[i].hit.next_vy;
            break;
        }
    }
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
    // printf("is ray facing right :: \n %d", data->ray[i].facing_right);
    // printf(" rotation angle %f\n", data->player.rotation_angle);
    // printf(" ray angle %f\n", data->ray[i].ray_angle);
}

double nornmalize_any_angle(double angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += (2 * PI);
    return (angle);
}

double caculate_distance_of_two_point(double x2, double y2, double x1, double y1)
{
    return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

void distance_normalizing(t_data *data, int i)
{
    double horz_distance;
    double ver_distance;

    horz_distance = caculate_distance_of_two_point(data->ray[i].horz_wallhit_x, data->ray[i].horz_wallhit_y,
                                                   data->player.x, data->player.y);
    ver_distance = caculate_distance_of_two_point(data->ray[i].vert_wallhit_x, data->ray[i].vert_wallhit_y,
                                                  data->player.x, data->player.y);
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

void draw_all_lines(t_data *data, int i, double angel)
{
    // data->player.rotation_angle = nornmalize_any_angle(data->player.rotation_angle);
    // data->ray[i].ray_angle = nornmalize_any_angle(data->ray[i].ray_angle);
    data->ray[i].ray_angle = angel;
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
    i = 0;
    while (i < NUM_RAYS)
    {
        distance_prj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        wall_stripe_height = (TILE_SIZE / data->ray[i].distance) * distance_prj_plane;
        draw_rect(data, i, ((WINDOW_HEIGHT) / 2) - (wall_stripe_height / 2), 1, wall_stripe_height, 0x000066);
        i++;
    }
}

int update_render(t_data *data)
{
    int i;
    double angel;
    mlx_clear_window(data->mlx, data->mlx_new_window);
    update_position(data);
    angel = data->player.rotation_angle - ((FOV) / 2);
    i = 0;
    while (i < (NUM_RAYS))
    {
        angel += ((FOV) / (NUM_RAYS));
        draw_all_lines(data, i, nornmalize_any_angle(angel));
        i++;
    }
    draw_rect(data, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xffffff);
    i = 0;
    while (i < NUM_RAYS)
    {
        draw_line_dda(data, FACTOR * data->player.x, FACTOR * data->player.y, FACTOR * data->ray[i].the_x_wallhit, FACTOR * data->ray[i].the_y_wallhit, 0xfffff);
        i++;
    }
    render_3d(data);
    draw_scene(data);
    draw_player(data);
    draw_line_dda(data, FACTOR * (data->player.x), FACTOR * (data->player.y), FACTOR * (data->player.x + cos(data->player.rotation_angle) * 30), FACTOR * (data->player.y + sin(data->player.rotation_angle) * 30), 0xFF0000);
    mlx_put_image_to_window(data->mlx, data->mlx_new_window, data->img_ptr, 0, 0);
    return (0);
}

int main()
{
    t_data data;
    char map[11][15] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
        {'1', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
        {'1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', 'S', '0', '0', '0', '1', '0', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};
    data.player = (t_player){.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .move_step = 0, .speed = 0.2, .turn_direction = 0, .walk_direction = 0, .rotation_angle = PI, .rotation_speed = 2 * (PI / 180)};
    // data.ray = (t_ray){.the_x_wallhit = 0, .the_y_wallhit = 0, .horz_wallhit_x = 0, .horz_wallhit_y = 0, .vert_wallhit_x = 0, .vert_wallhit_y = 0, .distance = 0, .ray_angle = PI / 2, .facing_down = 0, .facing_up = 0, .facing_left = 0, .facing_right = 0};

    data.mlx = mlx_init();
    data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "USM4");
    data.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.size_line, &data.endian);
    cpy_map(&data, map);
    // fill_rays_infos(&data);
    if (!mlx_hook(data.mlx_new_window, 2, 0, handle_keypress, &data))
        return ((perror("mlx hook failure")), 1);
    if (!mlx_hook(data.mlx_new_window, 3, 0, handle_keyrelease, &data))
        return ((perror("mlx hook failure")), 1);
    mlx_loop_hook(data.mlx, update_render, &data);
    mlx_loop(data.mlx);
}