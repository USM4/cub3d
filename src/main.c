/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 01:57:43 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/17 11:37:03 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_rgb(int r, int g, int b)
{
	return ((r * pow(2, 16)) + (g * pow(2, 8)) + b);
}

void	mlx_failure_protection(t_data *data)
{
	if (!mlx_hook(data->mlx_new_window, 2, 0, handle_keypress, data))
		display_errors3(-505);
	if (!mlx_hook(data->mlx_new_window, 3, 0, handle_keyrelease, data))
		display_errors3(-505);
	if (!mlx_hook(data->mlx_new_window, 17, 0, quit_window, data))
		display_errors3(-505);
}

t_elements	parsing(int ac, char **av)
{
	t_elements	elmt;
	char		**map_content;
	char		*mc_1d;
	char		**virtual_map;

	elmt.dmt.j = 0;
	if (ac < 2)
		display_errors(303);
	check_map_extension(av);
	elmt.dmt.fd = open(av[1], O_CREAT | O_RDONLY);
	if (elmt.dmt.fd == -1)
		display_errors(404);
	mc_1d = join_map_content(elmt.dmt.fd);
	map_content = ft_split_prs(mc_1d, '\n');
	virtual_map = create_virtual_map(map_content);
	elmt = check_map_elements(map_content, mc_1d);
	elmt.map_code = malloc((elmt.dmt.lines - elmt.dmt.i + 1) * sizeof(char *));
	elmt.map_code[elmt.dmt.lines - elmt.dmt.i] = NULL;
	check_map_characters(map_content, elmt.dmt);
	check_map_4sides_wall(virtual_map, elmt.dmt);
	check_map_wall(virtual_map, elmt.dmt);
	while (virtual_map[elmt.dmt.i])
		elmt.map_code[elmt.dmt.j++] = virtual_map[elmt.dmt.i++];
	return (elmt.map_content = map_content, \
	elmt.virtual_map = virtual_map, free(mc_1d), elmt);
}

void	foor_ceil(t_data *data)
{
	data->floor = convert_rgb(ft_atoi_prs(data->bridge.fcc.floor_rgb[0]), \
	ft_atoi_prs(data->bridge.fcc.floor_rgb[1]), \
	ft_atoi_prs(data->bridge.fcc.floor_rgb[2]));
	data->ceiling = convert_rgb(ft_atoi_prs(data->bridge.fcc.ceiling_rgb[0]), \
	ft_atoi_prs(data->bridge.fcc.ceiling_rgb[1]), \
	ft_atoi_prs(data->bridge.fcc.ceiling_rgb[2]));
	lightweight_memory(data->bridge.fcc.floor_rgb);
	lightweight_memory(data->bridge.fcc.ceiling_rgb);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.bridge = parsing(ac, av);
	foor_ceil(&data);
	initialize_my_structs(&data);
	data.ray = malloc(data.val.window_width * sizeof(t_ray));
	if (!data.ray)
		return (1);
	data.map = data.bridge.map_code;
	data.bridge.dmt.lines = num_rows_counter(data.map);
	initialize_player_position(&data);
	initialize_player_facing(&data);
	data.mlx = mlx_init();
	data.mlx_new_window = mlx_new_window(data.mlx, \
	data.val.window_width, data.val.window_height, "USM4");
	data.img_ptr = mlx_new_image(data.mlx, \
	data.val.window_width, data.val.window_height);
	data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
			&data.size_line, &data.endian);
	mlx_failure_protection(&data);
	initialize_mlx_ingredients2(&data);
	mlx_loop_hook(data.mlx, update_render, &data);
	mlx_loop(data.mlx);
	return (lightweight_memory(data.bridge.virtual_map),
		lightweight_memory(data.bridge.map_content), 0);
}

// void	draw_line_dda(t_data *data, double x1, double y1, \
// double x2, double y2, int color)
// {
// 	data->line.diff_x = x2 - x1;
// 	data->line.diff_y = y2 - y1;
// 	if (my_own_abs(data->line.diff_x) > my_own_abs(data->line.diff_y))
// 		data->line.steps = my_own_abs(data->line.diff_x);
// 	else
// 		data->line.steps = my_own_abs(data->line.diff_y);
// 	data->line.x_increment = (float)(data->line.diff_x) / \
// 				(float)(data->line.steps);
// 	data->line.y_increment = (float)data->line.diff_y / (float)data->line.steps;
// 	data->line.x = (float)x1;
// 	data->line.y = (float)y1;
// 	my_mlx_pixel_put(data, my_own_round(data->line.x), \
// 		my_own_round(data->line.y), color);
// 	while (data->line.steps > 0)
// 	{
// 		data->line.x += data->line.x_increment;
// 		data->line.y += data->line.y_increment;
// 		my_mlx_pixel_put(data, my_own_round(data->line.x),
// 			my_own_round(data->line.y), color);
// 		data->line.steps--;
// 	}
// }

// void	render_game(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	render_3d(data);
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
// }