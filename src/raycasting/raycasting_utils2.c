/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:41:18 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/12 11:46:35 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_all_lines(t_data *data, int i, double angle)
{
	data->ray[i].ray_angle = angle;
	facing_normalization(&data->ray[i]);
	horizontal(data, i);
	vertical(data, i);
	distance_normalizing(data, i);
}
