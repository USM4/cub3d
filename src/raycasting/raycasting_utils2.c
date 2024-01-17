/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:41:18 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/17 02:39:37 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_for_hz_intersection(t_data *data, int i)
{
	int	decrement;

	decrement = 0;
	while (data->ray[i].hit.next_hx >= 0 && \
	data->ray[i].hit.next_hx <= (data->bridge.dmt.longest_line * TILE_SIZE) && \
	data->ray[i].hit.next_hy >= 0 && data->ray[i].hit.next_hy \
	<= (data->bridge.dmt.lines * TILE_SIZE))
	{
		if (data->ray[i].facing_up == 1)
			decrement = 1;
		else
			decrement = 0;
		if (check_is_wall(data->ray[i].hit.next_hx, data->ray[i].\
		hit.next_hy - decrement, data))
		{
			data->ray[i].horz_wallhit_x = data->ray[i].hit.next_hx;
			data->ray[i].horz_wallhit_y = data->ray[i].hit.next_hy;
			break ;
		}
		else
		{
			data->ray[i].hit.next_hx += data->ray[i].hit.x_step;
			data->ray[i].hit.next_hy += data->ray[i].hit.y_step;
		}
	}
}

void	horizontal(t_data *data, int i)
{
	data->ray[i].hit.next_hx = 0;
	data->ray[i].hit.next_hy = 0;
	data->ray[i].hit.y_point = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (data->ray[i].facing_down == 1)
		data->ray[i].hit.y_point += TILE_SIZE;
	data->ray[i].hit.x_point = data->player.x + (data->ray[i].hit. \
	y_point - data->player.y) / tan(data->ray[i].ray_angle);
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
	loop_for_hz_intersection(data, i);
	data->ray[i].horz_wallhit_x = data->ray[i].hit.next_hx;
	data->ray[i].horz_wallhit_y = data->ray[i].hit.next_hy;
}

void	loop_for_vert_intersection(t_data *data, int i)
{
	int	var;

	var = 0;
	while ((data->ray[i].hit.next_vx >= 0 && data->ray[i].hit.next_vx \
	<= (data->bridge.dmt.longest_line * TILE_SIZE)) && \
	(data->ray[i].hit.next_vy >= 0 && \
	data->ray[i].hit.next_vy <= (data->bridge.dmt.lines * TILE_SIZE)))
	{
		if (data->ray[i].facing_left == 1)
			var = 1;
		else
			var = 0;
		if (check_is_wall(data->ray[i].hit.next_vx - var, \
		data->ray[i].hit.next_vy, data))
		{
			data->ray[i].vert_wallhit_x = data->ray[i].hit.next_vx;
			data->ray[i].vert_wallhit_y = data->ray[i].hit.next_vy;
			break ;
		}
		else
		{
			data->ray[i].hit.next_vx += data->ray[i].hit.x_step;
			data->ray[i].hit.next_vy += data->ray[i].hit.y_step;
		}
	}
}

void	vertical(t_data *data, int i)
{
	data->ray[i].hit.next_vx = 0;
	data->ray[i].hit.next_vy = 0;
	data->ray[i].hit.x_point = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (data->ray[i].facing_right == 1)
		data->ray[i].hit.x_point += TILE_SIZE;
	data->ray[i].hit.y_point = data->player.y + (data->ray[i].hit.\
	x_point - data->player.x) * tan(data->ray[i].ray_angle);
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
	loop_for_vert_intersection(data, i);
	data->ray[i].vert_wallhit_x = data->ray[i].hit.next_vx;
	data->ray[i].vert_wallhit_y = data->ray[i].hit.next_vy;
}

void	draw_all_lines(t_data *data, int i, double angle)
{
	data->ray[i].ray_angle = angle;
	facing_normalization(&data->ray[i]);
	horizontal(data, i);
	vertical(data, i);
	distance_normalizing(data, i);
}
