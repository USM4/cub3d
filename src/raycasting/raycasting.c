/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:22:17 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/17 11:35:08 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_game_state(t_data *data)
{
	int		i;
	double	angle;
	double	angle_increment;

	i = 0;
	data->player.rotation_angle = \
	nornmalize_any_angle(data->player.rotation_angle);
	angle_increment = (data->val.fov) / (data->val.window_width);
	angle = data->player.rotation_angle - ((data->val.fov) / 2);
	data->params = (t_draw){.x = 0, .y = 0, .width = data->val.window_width \
	, .height = data->val.window_height / 2, .color = data->ceiling};
	draw_rect(data);
	data->params = (t_draw){.x = 0, .y = data->val.window_height / 2, .width = \
	data->val.window_width, .height = data->val.window_height \
	- (data->val.window_height / 2), \
	.color = data->floor};
	draw_rect(data);
	while (i < data->val.window_width)
	{
		data->ray[i] = (t_ray){0};
		draw_all_lines(data, i, nornmalize_any_angle(angle));
		angle += angle_increment;
		i++;
	}
}

void	render_game(t_data *data)
{
	render_3d(data);
}

int	update_render(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_new_window);
	update_position(data);
	update_game_state(data);
	render_game(data);
	mlx_put_image_to_window(data->mlx, \
	data->mlx_new_window, data->img_ptr, 0, 0);
	return (0);
}
