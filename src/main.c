/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:46:05 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/15 19:44:53 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_dda(t_data *data, double x1, double y1,\
double x2, double y2, int color)
{
	data->line.diff_x = x2 - x1;
	data->line.diff_y = y2 - y1;
	if (my_own_abs(data->line.diff_x) > my_own_abs(data->line.diff_y))
		data->line.steps = my_own_abs(data->line.diff_x);
	else
		data->line.steps = my_own_abs(data->line.diff_y);
	data->line.x_increment = (float)(data->line.diff_x) / \
				(float)(data->line.steps);
	data->line.y_increment = (float)data->line.diff_y / (float)data->line.steps;
	data->line.x = (float)x1;
	data->line.y = (float)y1;
	my_mlx_pixel_put(data, my_own_round(data->line.x), \
		my_own_round(data->line.y), color);
	while (data->line.steps > 0)
	{
		data->line.x += data->line.x_increment;
		data->line.y += data->line.y_increment;
		my_mlx_pixel_put(data, my_own_round(data->line.x),
			my_own_round(data->line.y), color);
		data->line.steps--;
	}
}

void	initialize_mlx_ingredients2(t_data *data)
{
	int	tmp;

	data->textures[0].n_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.test.no_path, &data->textures[0].width, \
			&data->textures[0].height);
	data->textures[1].s_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.test.so_path, &data->textures[1].width, \
			&data->textures[1].height);
	data->textures[2].e_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.test.ea_path, &data->textures[2].width, \
			&data->textures[2].height);
	data->textures[3].w_img = mlx_xpm_file_to_image(data->mlx,
			data->bridge.test.we_path, &data->textures[3].width, \
			&data->textures[3].height);
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

void set_facing(t_data *data, char c)
{
	if (c == 'N')
		data->player.rotation_angle = 1.5 * PI;
	else if(c == 'S') 
		data->player.rotation_angle = PI / 2;
	else if(c == 'E') 
		data->player.rotation_angle = 0;
	else if(c == 'W') 
		data->player.rotation_angle = PI;
}

void	initialize_player_facing(t_data *data)
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
		if(flag)
			break ;
		i++;
	}
	set_facing(data, data->map[i][j]);
}

int main(int ac, char **av)
{
	t_data		data;
	char		**map_content;
	char		*mc_1d;
	char		**map_code;
	char		**virtual_map;
	int			fd;
	t_dimention	dmt;
	t_elements	test;
	int 		i;

	i = 0;
	dmt = (t_dimention){0};
	test = (t_elements){0};
	if (ac < 2)
		display_errors(303);
	check_map_extension(av);
	fd = open(av[1], O_CREAT | O_RDONLY);
	if (fd == -1)
		display_errors(404);
	mc_1d = join_map_content(fd);
	map_content = ft_split_prs(mc_1d, '\n');
	virtual_map = create_virtual_map(map_content);
	dmt = check_map_elements(map_content, mc_1d);
	map_code = malloc((dmt.lines - dmt.i + 1) * sizeof(char *));
	map_code[dmt.lines - dmt.i] = NULL;
	check_map_characters(map_content, dmt);
	check_map_4sides_wall(virtual_map, dmt);
	check_map_wall(virtual_map, dmt);
	while (virtual_map[dmt.i])
		map_code[i++] = virtual_map[dmt.i++];
	dmt.num_rows = num_rows_counter(map_code);
	data.bridge = dmt;
	initialize_my_structs(&data);
	data.ray = malloc(data.val.window_width * sizeof(t_ray));
	if (!data.ray)
		return (1);
	cpy_map(&data, map_code);
	initialize_player_position(&data);
	initialize_player_facing(&data);
	data.mlx = mlx_init();
	data.mlx_new_window = mlx_new_window(data.mlx, \
	data.val.window_width, data.val.window_height, "USM4");
	data.img_ptr = mlx_new_image(data.mlx, \
	data.val.window_width, data.val.window_height);
	data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
			&data.size_line, &data.endian);
	if (!mlx_hook(data.mlx_new_window, 2, 0, handle_keypress, &data))
		return ((perror("mlx hook failure")), 1);
	if (!mlx_hook(data.mlx_new_window, 3, 0, handle_keyrelease, &data))
		return ((perror("mlx hook failure")), 1);
	if (!mlx_hook(data.mlx_new_window, 17, 0, quit_window, &data))
		return ((perror("mlx hook failure")), 1);
	// printf("ceiling %s \n", data.bridge.test.ceiling_color);
	initialize_mlx_ingredients2(&data);
	mlx_loop_hook(data.mlx, update_render, &data);
	mlx_loop(data.mlx);
}
