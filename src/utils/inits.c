/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:20:11 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/17 02:38:58 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_mlx_ingredients2(t_data *data)
{
	int	tmp;

	data->textures[0].n_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.no_path, &data->textures[0].width, \
			&data->textures[0].height);
	data->textures[1].s_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.so_path, &data->textures[1].width, \
			&data->textures[1].height);
	data->textures[2].e_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.ea_path, &data->textures[2].width, \
			&data->textures[2].height);
	data->textures[3].w_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.we_path, &data->textures[3].width, \
			&data->textures[3].height);
	handle_textures_failing(data);
	data->textures[0].arr = (uint32_t *)mlx_get_data_addr(data->textures[0] \
	.n_img, &tmp, &tmp, &tmp);
	data->textures[1].arr = (uint32_t *)mlx_get_data_addr(data->textures[1] \
	.s_img, &tmp, &tmp, &tmp);
	data->textures[2].arr = (uint32_t *)mlx_get_data_addr(data->textures[2] \
	.e_img, &tmp, &tmp, &tmp);
	data->textures[3].arr = (uint32_t *)mlx_get_data_addr(data->textures[3] \
	.w_img, &tmp, &tmp, &tmp);
}

void	initialize_my_structs(t_data *data)
{
	data->val = (t_utils){.window_height = 1500,
		.window_width = 1800,
		.fov = (60 * (PI / 180))};
	data->player = (t_player){.x = 0,
		.y = 0,
		.move_step = 0,
		.speed = 0.5,
		.turn_direction = 0,
		.walk_direction = 0,
		.flag = 0,
		.rotation_angle = PI / 2,
		.rotation_speed = 3 * (PI / 180)};
	data->offset = (t_textures){0};
	data->params = (t_draw){0};
}

int	num_rows_counter(char **map)
{
	int	count;

	count = 0;
	while (map[count])
		count++;
	return (count);
}

void	initialize_player_position(t_data *data)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || \
			data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				flag = 1;
				break ;
			}
			j++;
		}
		if (flag)
			break ;
		i++;
	}
	data->player.x = (j * TILE_SIZE) - (TILE_SIZE / 2);
	data->player.y = (i * TILE_SIZE) - (TILE_SIZE / 2);
}

void	initialize_player_facing(t_data *data)
{
	char	c;

	c = get_start_point(data->map);
	if (c == 'N')
		data->player.rotation_angle = 1.5 * PI;
	else if (c == 'S')
		data->player.rotation_angle = PI / 2;
	else if (c == 'E')
		data->player.rotation_angle = 0;
	else if (c == 'W')
		data->player.rotation_angle = PI;
}
