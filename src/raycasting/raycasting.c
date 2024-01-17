/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:22:17 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/16 23:16:17 by hlabouit         ###   ########.fr       */
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
	, .height = data->val.window_height / 2, .color = 0x0};
	draw_rect(data);
	data->params = (t_draw){.x = 0, .y = data->val.window_height / 2, .width = \
	data->val.window_width, .height = data->val.window_height \
	- (data->val.window_height / 2), \
	.color = 0x054d14};
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
	int	i;

	i = 0;
	render_3d(data);
	// draw_scene(data);
	// draw_player(data);
	// while (i < data->val.window_width)
	// {
	// 	draw_line_dda(data, FACTOR * data->player.x, FACTOR * data->player.y, \
	// 	FACTOR * data->ray[i].the_x_wallhit, \
	// 	FACTOR * data->ray[i].the_y_wallhit, 0xfc6500);
	// 	i++;
	// }
	// draw_line_dda(data, FACTOR * (data->player.x), \
	// FACTOR * (data->player.y), FACTOR * \
	// (data->player.x + cos(data->player.rotation_angle) * 30), \
	// FACTOR * (data->player.y + \
	// sin(data->player.rotation_angle) * 30), 0xfcdb03);
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
