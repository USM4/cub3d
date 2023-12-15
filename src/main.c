/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:47:40 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/14 22:46:48 by oredoine         ###   ########.fr       */
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
            // printf("gere x : %d - y : %d \n", j, i);
            my_mlx_pixel_put(data, j, i, color);
            j++;
        }
        i++;
    }
}

int my_own_round(float num)
{
    double fractional_part;

    fractional_part = num - (int) num;
    if(fractional_part >= 0.5)
        return((int)(num + 1.0));
    else
        return((int)num);
}

int my_own_abs(int num)
{
    if (num < 0)
        num *= -1;
    return(num);
}

void draw_line_dda(t_data *data, int x1, int x2, int y1, int y2)
{
    data->line.diff_x = x2 - x1;
    data->line.diff_y = y2 - y1;
    data->line.steps = my_own_abs(data->line.diff_x) > my_own_abs(data->line.diff_y) ? my_own_abs(data->line.diff_x) : my_own_abs(data->line.diff_y);
    data->line.x_increment = (float)(data->line.diff_x) / (float)(data->line.steps);
    data->line.y_increment = (float)data->line.diff_y / (float)data->line.steps;
    data->line.x = (float)x1;
    data->line.y = (float)y1;
    my_mlx_pixel_put(data, my_own_round(data->line.x), my_own_round(data->line.y), 0xFF0000);
    printf("steps = %d\n", data->line.steps);
    while(data->line.steps > 0)
    {
        data->line.x += data->line.x_increment;
        data->line.y += data->line.y_increment;
        printf("X = %d\n",  my_own_round(data->line.x));
        printf("Y = %d\n",  my_own_round(data->line.y));
        my_mlx_pixel_put(data, my_own_round(data->line.x), my_own_round(data->line.y), 0xFF0000);
        data->line.steps--;
    }
}

int	handle_keypress(int keycode, t_data *data)
{
    if (keycode == 123)
	{
		data->player.turn_direction = -1;
		printf("LEFT : %d\n", data->player.turn_direction);
	}
	else if (keycode == 124)
	{
        data->player.turn_direction = 1;
        printf("RIGHT : %d\n", data->player.turn_direction);
	}
	else if (keycode == 125)
	{
        data->player.walk_direction = -1;
        printf("BACK : %d\n", data->player.walk_direction);
	}
	else if (keycode == 126)
	{
		data->player.walk_direction = 1;
        printf("FRONT : %d\n", data->player.walk_direction);
	}
    return(0);
}
    
int	handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == 123)
		data->player.turn_direction = 0;
	else if (keycode == 124)
        data->player.turn_direction = 0;
	else if (keycode == 125)
        data->player.walk_direction = 0;
	else if (keycode == 126)
		data->player.walk_direction = 0;
    return(0);
}

int main()
{
    t_data data;
    t_tile infos;
    char map[][15] = {
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
    t_player p = {.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, 
    .rotation_angle = PI / 2, .rotation_speed = 5, .turn_direction = 0, .walk_direction = 0, .speed = 1.5};
    (void)p;
    data.mlx = mlx_init();
    data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "USM4");
    data.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.size_line, &data.endian);
    int i = 0;
    int j;
    int x;
    int y;
    while (i < NUM_ROWS)
    {
        j = 0;
        while (j < NUM_COLS)
        {
            infos.tile_x = j * TILE_SIZE;
            infos.tile_y = i * TILE_SIZE;
            infos.tile_color = (map[i][j] == '1' ? 0x000066 : 0x0);
            if (map[i][j] == 'S')
            {
                draw_rect(&data, infos.tile_x, infos.tile_y, TILE_SIZE, TILE_SIZE, 0x0);
                infos.tile_color = 0xFFFFFF;
                x = infos.tile_x + 2 * (TILE_SIZE / 3);
                y = infos.tile_y + 2 * (TILE_SIZE / 3);
                draw_rect(&data, infos.tile_x + (TILE_SIZE / 3), infos.tile_y + (TILE_SIZE / 3), TILE_SIZE / 3, TILE_SIZE / 3, infos.tile_color);
            }
            else
                draw_rect(&data, infos.tile_x, infos.tile_y, TILE_SIZE, TILE_SIZE, infos.tile_color);
            j++;
        }
        i++;
    }
    draw_line_dda(&data, x, WINDOW_WIDTH - 1, y, WINDOW_HEIGHT - 1);
    if (!mlx_hook(data.mlx_new_window, 2, 0L, handle_keypress, &data))
        return((perror("mlx hook failure")), 1);
    if (!mlx_hook(data.mlx_new_window, 3, 0, handle_keyrelease, &data))
        return((perror("mlx hook failure")), 1);
    mlx_put_image_to_window(data.mlx, data.mlx_new_window, data.img_ptr, 0, 0);
    mlx_loop(data.mlx);
}