/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:31:31 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/13 21:32:35 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 123)
		data->player.turn_direction = -1;
	else if (keycode == 124)
		data->player.turn_direction = 1;
	else if (keycode == 0)
	{
		data->player.flag = -1;
		data->player.walk_direction = 1;
	}
	else if (keycode == 2)
	{
		data->player.flag = 1;
		data->player.walk_direction = 1;
	}
	else if (keycode == 13)
		data->player.walk_direction = 1;
	else if (keycode == 1)
		data->player.walk_direction = -1;
	else if (keycode == 53)
		exit(0);
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == 123 || keycode == 124)
		data->player.turn_direction = 0;
	if (keycode == 13 || keycode == 1)
	{
		data->player.walk_direction = 0;
		data->player.move_step = 0;
	}
	if (keycode == 2 || keycode == 0)
	{
		data->player.flag = 0;
		data->player.walk_direction = 0;
		data->player.move_step = 0;
	}
	return (0);
}
