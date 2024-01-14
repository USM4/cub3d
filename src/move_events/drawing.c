/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:33:42 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/14 20:21:17 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->bridge.num_rows)
	{
		j = 0;
		while (j < data->bridge.longest_line)
		{
			if (data->map[i][j] == 'S')
			{
				data->params = (t_draw){.x = FACTOR * data->player.x, \
				.y = FACTOR * data->player.y, .width = FACTOR \
				* (TILE_SIZE / 3), .height = FACTOR * \
				(TILE_SIZE / 3), .color = 0xfcdb03};
				draw_rect(data);
			}
			j++;
		}
		i++;
	}
}

void	draw_scene(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->bridge.num_rows)
	{
		j = 0;
		while (j < data->bridge.longest_line)
		{
			data->tile.tile_x = j * TILE_SIZE;
			data->tile.tile_y = i * TILE_SIZE;
			if (data->map[i][j] == '1')
				data->tile.tile_color = 0x000066;
			else
				data->tile.tile_color = 0x0;
			data->params = (t_draw){.x = FACTOR * data->tile.tile_x, \
			.y = FACTOR * data->tile.tile_y, .width = FACTOR * TILE_SIZE \
			, .height = FACTOR * TILE_SIZE, .color = data->tile.tile_color};
			draw_rect(data);
			j++;
		}
		i++;
	}
}

void	update_position(t_data *data)
{
	double	new_x;
	double	new_y;
	double	angle;

	data->player.rotation_angle += data->player.turn_direction * \
						data->player.rotation_speed;
	angle = data->player.rotation_angle + (data->player.flag * (PI / 2));
	new_x = data->player.x + cos(angle) * (data->player.move_step);
	new_y = data->player.y + sin(angle) * (data->player.move_step);
	if (!check_is_wall(new_x + 10, new_y, data) && \
		!check_is_wall(new_x - 10, new_y, data) && \
		!check_is_wall(new_x, new_y + 10, data) && \
		!check_is_wall(new_x, new_y - 10, data))
	{
		data->player.move_step += data->player.walk_direction * \
								data->player.speed;
		data->player.x = new_x;
		data->player.y = new_y;
	}
}
