/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:30:28 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/15 17:27:38 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	facing_normalization(t_ray *ray)
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

double	nornmalize_any_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

double	caculate_distance_of_two_point(double x2, double y2, \
double x1, double y1)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

int	check_is_wall(double x, double y, t_data *data)
{
	int	i;
	int	j;

	x /= TILE_SIZE;
	y /= TILE_SIZE;
	i = floor(y);
	j = floor(x);
	if (i <= 0 || i >= data->bridge.num_rows || j <= 0 || \
		j >= data->bridge.longest_line || data->map[i][j] == '1')
		return (1);
	return (0);
}

void	distance_normalizing(t_data *data, int i)
{
	double	horz_distance;
	double	ver_distance;

	horz_distance = caculate_distance_of_two_point(data->ray[i].horz_wallhit_x, \
		data->ray[i].horz_wallhit_y, data->player.x, data->player.y);
	ver_distance = caculate_distance_of_two_point(data->ray[i].vert_wallhit_x,
			data->ray[i].vert_wallhit_y, data->player.x, data->player.y);
	if (horz_distance > ver_distance)
	{
		data->ray[i].the_x_wallhit = data->ray[i].vert_wallhit_x;
		data->ray[i].the_y_wallhit = data->ray[i].vert_wallhit_y;
		data->ray[i].distance = ver_distance;
		data->ray[i].flag_v = 1;
		data->ray[i].flag_h = 0;
	}
	else
	{
		data->ray[i].the_x_wallhit = data->ray[i].horz_wallhit_x;
		data->ray[i].the_y_wallhit = data->ray[i].horz_wallhit_y;
		data->ray[i].distance = horz_distance;
		data->ray[i].flag_h = 1;
		data->ray[i].flag_v = 0;
	}
}
