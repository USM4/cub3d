/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:38:09 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/15 15:25:16 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_texture(t_data *data, int i)
{
	if (data->ray[i].facing_up && data->ray[i].flag_h)
		data->offset.id = 0;
	else if (data->ray[i].facing_down && data->ray[i].flag_h)
		data->offset.id = 1;
	else if (data->ray[i].facing_right && data->ray[i].flag_v)
		data->offset.id = 2;
	else if (data->ray[i].facing_left && data->ray[i].flag_v)
		data->offset.id = 3;
}

void	puting_on_wall(t_data *data, int i, \
double wall_stripe_height, double wallheight)
{
	int		color;
	double	from_top;
	double	wall_bottom;
	double	texture_x;
	double	texture_y;

	color = 0;
	from_top = 0;
	texture_x = data->offset.x;
	texture_y = 0;
	wall_bottom = ((double)data->val.window_height / 2) + (wallheight / 2);
	while (data->offset.y < wall_bottom)
	{
		from_top = data->offset.y + (wall_stripe_height / 2) \
		- ((double)data->val.window_height / 2);
		texture_y = (int)((double)(from_top) *\
		(data->textures[data->offset.id].height / wall_stripe_height));
		color = data->textures[data->offset.id].arr[((int)texture_y * \
		data->textures[data->offset.id].width) + (int)texture_x];
		my_mlx_pixel_put(data, i, data->offset.y, color);
		data->offset.y++;
	}
}

double	calculate_wall_dementions(t_data *data, int i)
{
	double	fish_bowl;
	double	distance_prj_plane;
	double	wall_stripe_height;

	fish_bowl = data->ray[i].distance * \
	cos(data->ray[i].ray_angle - data->player.rotation_angle);
	distance_prj_plane = ((double)data->val.window_width / 2) / \
	tan(data->val.fov / 2);
	wall_stripe_height = (TILE_SIZE / fish_bowl) * distance_prj_plane;
	return (wall_stripe_height);
}

void	render_textures(t_data *data, int i, double wall_stripe_height, \
double wallheight)
{
	double	texture_x;

	texture_x = 0;
	select_texture(data, i);
	if (data->ray[i].flag_h)
		data->offset.x = ((int)(data->ray[i].the_x_wallhit * \
		((double)data->textures[data->offset.id].width / TILE_SIZE))) % \
		data->textures[data->offset.id].width;
	else if (data->ray[i].flag_v)
		data->offset.x = ((int)(data->ray[i].the_y_wallhit * \
		((double)data->textures[data->offset.id].width \
		/ TILE_SIZE))) % data->textures[data->offset.id].width;
	puting_on_wall(data, i, wall_stripe_height, wallheight);
}

void	render_3d(t_data *data)
{
	int		i;
	double	wall_stripe_height;
	double	wall_top;
	double	wallheight;

	i = 0;
	wall_stripe_height = 0;
	wallheight = 0;
	while (i < data->val.window_width)
	{
		wall_stripe_height = calculate_wall_dementions(data, i);
		wallheight = wall_stripe_height;
		if (wallheight > data->val.window_height)
			wallheight = data->val.window_height;
		wall_top = ((double)data->val.window_height / 2) - (wallheight / 2);
		if (wall_top < 0)
			data->offset.y = 0;
		else
			data->offset.y = wall_top;
		render_textures(data, i, wall_stripe_height, wallheight);
		i++;
	}
}
