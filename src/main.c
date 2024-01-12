/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:46:05 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/12 17:49:34 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_dda(t_data *data, double x1, double y1,
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
		my_mlx_pixel_put(data, my_own_round(data->line.x), \
					my_own_round(data->line.y), color);
		data->line.steps--;
	}
}

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

// void	fill_draw_members(double x, double y, double width, double height)
// {
		
// }

void	draw_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < NUM_ROWS)
	{
		j = 0;
		while (j < NUM_COLS)
		{
			if (data->map[i][j] == 'S')
				draw_rect(data, FACTOR * data->player.x, FACTOR * \
				data->player.y, FACTOR * (TILE_SIZE / 3), FACTOR * \
				(TILE_SIZE / 3), 0xfcdb03);
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
	while (i < NUM_ROWS)
	{
		j = 0;
		while (j < NUM_COLS)
		{
			data->tile.tile_x = j * TILE_SIZE;
			data->tile.tile_y = i * TILE_SIZE;
			if (data->map[i][j] == '1')
				data->tile.tile_color = 0x000066;
			else
				data->tile.tile_color = 0x0;
			draw_rect(data, FACTOR * data->tile.tile_x, \
			FACTOR * data->tile.tile_y, FACTOR * TILE_SIZE, \
			FACTOR * TILE_SIZE, data->tile.tile_color);
			j++;
		}
		i++;
	}
}

void horizontal(t_data *data, int i)
{
	int	decrement;
	// find the y coordinate of the closest horizontal tile
	decrement = 0;
	data->ray[i].hit.next_hx = 0;
	data->ray[i].hit.next_hy = 0;
	data->ray[i].hit.y_point = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (data->ray[i].facing_down == 1)
		data->ray[i].hit.y_point += TILE_SIZE;
	data->ray[i].hit.x_point = data->player.x + (data->ray[i].hit.y_point - data->player.y) / tan(data->ray[i].ray_angle);
	data->ray[i].hit.y_step = TILE_SIZE;
	if (data->ray[i].facing_up == 1)
		data->ray[i].hit.y_step *= -1;
	data->ray[i].hit.x_step = TILE_SIZE / tan(data->ray[i].ray_angle);
	if ((data->ray[i].facing_left && data->ray[i].hit.x_step > 0))
		data->ray[i].hit.x_step *= -1;
	if (data->ray[i].facing_right && data->ray[i].hit.x_step < 0)
		data->ray[i].hit.x_step *= -1;
	data->ray[i].hit.next_hx = data->ray[i].hit.x_point;
	data->ray[i].hit.next_hy = data->ray[i].hit.y_point;
		while (data->ray[i].hit.next_hx >= 0 && data->ray[i].hit.next_hx <= WINDOW_WIDTH && data->ray[i].hit.next_hy >= 0 && data->ray[i].hit.next_hy <= WINDOW_HEIGHT)
	{
		if (data->ray[i].facing_up == 1)
			decrement = 1;
		else
			decrement = 0;
		if (check_is_wall(data->ray[i].hit.next_hx, data->ray[i].hit.next_hy - decrement, data))
		{
			data->ray[i].horz_wallhit_x = data->ray[i].hit.next_hx;
			data->ray[i].horz_wallhit_y = data->ray[i].hit.next_hy;
			break ;
		}
		else
		{
			data->ray[i].hit.next_hx += data->ray[i].hit.x_step;
			data->ray[i].hit.next_hy += data->ray[i].hit.y_step;
		}
	}
	data->ray[i].horz_wallhit_x = data->ray[i].hit.next_hx;
	data->ray[i].horz_wallhit_y = data->ray[i].hit.next_hy;
}

void vertical(t_data *data, int i)
{
	int var;
	// find the x coordinate of the closest horizontal tile
	var = 0;
	data->ray[i].hit.next_vx = 0;
	data->ray[i].hit.next_vy = 0;
	data->ray[i].hit.x_point = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (data->ray[i].facing_right == 1)
		data->ray[i].hit.x_point += TILE_SIZE;
	data->ray[i].hit.y_point = data->player.y + (data->ray[i].hit.x_point - data->player.x) * tan(data->ray[i].ray_angle);
	data->ray[i].hit.x_step = TILE_SIZE;
	if (data->ray[i].facing_left)
		data->ray[i].hit.x_step *= -1;
	data->ray[i].hit.y_step = TILE_SIZE * tan(data->ray[i].ray_angle);
	if ((data->ray[i].facing_up && data->ray[i].hit.y_step > 0))
		data->ray[i].hit.y_step *= -1;
	else
		data->ray[i].hit.y_step *= 1;
	if ((data->ray[i].facing_down && data->ray[i].hit.y_step < 0))
		data->ray[i].hit.y_step *= -1;
	else
		data->ray[i].hit.y_step *= 1;
	data->ray[i].hit.next_vx = data->ray[i].hit.x_point;
	data->ray[i].hit.next_vy = data->ray[i].hit.y_point;
	while ((data->ray[i].hit.next_vx >= 0 && data->ray[i].hit.next_vx <= WINDOW_WIDTH) && (data->ray[i].hit.next_vy >= 0 && data->ray[i].hit.next_vy <= WINDOW_HEIGHT))
	{
		if (data->ray[i].facing_left == 1)
			var = 1;
		else
			var = 0;
		if (check_is_wall(data->ray[i].hit.next_vx - var, data->ray[i].hit.next_vy, data))
		{
			data->ray[i].vert_wallhit_x = data->ray[i].hit.next_vx;
			data->ray[i].vert_wallhit_y = data->ray[i].hit.next_vy;
			break ;
		}
		else
		{
			data->ray[i].hit.next_vx += data->ray[i].hit.x_step;
			data->ray[i].hit.next_vy += data->ray[i].hit.y_step;
		}
	}
	data->ray[i].vert_wallhit_x = data->ray[i].hit.next_vx;
	data->ray[i].vert_wallhit_y = data->ray[i].hit.next_vy;
}

void update_position(t_data *data)
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

int	select_texture(t_data *data, int i)
{
	int	id;

	id = 0;
	if (data->ray[i].facing_up && data->ray[i].flag_h)
		return (id);
	else if (data->ray[i].facing_down && data->ray[i].flag_h)
		id = 1;
	else if (data->ray[i].facing_right && data->ray[i].flag_v)
		id = 2;
	else if (data->ray[i].facing_left && data->ray[i].flag_v)
		id = 3;
	return (id);
}

void render_textures(t_data *data, int i, double wall_bottom, double wall_stripe_height)
{
	double	texture_x;
	double	texture_y;
	double	from_top;
	int		color;
	int		id;

	texture_x = 0;
	texture_y = 0;
	color = 0;
	id = select_texture(data, i);
	if (data->ray[i].flag_h)
		data->offset.x = ((int)(data->ray[i].the_x_wallhit * \
		((double)data->textures[id].width / TILE_SIZE))) % \
		data->textures[id].width;
	else if (data->ray[i].flag_v)
		data->offset.x = ((int)(data->ray[i].the_y_wallhit * \
		((double)data->textures[id].width \
		/ TILE_SIZE))) % data->textures[id].width;
	texture_x = data->offset.x;
	while (data->offset.y < wall_bottom)
	{
		from_top = data->offset.y + (wall_stripe_height / 2) \
		- ((double)WINDOW_HEIGHT / 2);
		texture_y = (int)((double)(from_top) *\
		(data->textures[id].height / wall_stripe_height));
		color = data->textures[id].arr[((int)texture_y * \
		data->textures[id].width) + (int)texture_x];
		my_mlx_pixel_put(data, i, data->offset.y, color);
		data->offset.y++;
	}
}

void render_3d(t_data *data)
{
	int		i;
	double	distance_prj_plane;
	double	wall_stripe_height;
	double	fish_bowl;
	double	wall_top;
	double	wall_bottom;
	double	wallheight;

	i = 0;
	wallheight = 0;
	while (i < NUM_RAYS)
	{
		fish_bowl = data->ray[i].distance * cos(data->ray[i].ray_angle \
		- data->player.rotation_angle);
		distance_prj_plane = ((double)WINDOW_WIDTH / 2) / tan(FOV / 2);
		wall_stripe_height = (TILE_SIZE / fish_bowl) * distance_prj_plane;
		wallheight = wall_stripe_height;
		if (wallheight > WINDOW_HEIGHT)
			wallheight = WINDOW_HEIGHT;
		wall_top = ((double)WINDOW_HEIGHT / 2) - (wallheight / 2);
		wall_bottom = ((double)WINDOW_HEIGHT / 2) + (wallheight / 2);
		if (wall_top < 0)
			data->offset.y = 0;
		else
			data->offset.y = wall_top;
		render_textures(data, i, wall_bottom, wall_stripe_height);
		i++;
	}
}

int	update_render(t_data *data)
{
	int		i;
	double	angle;
	double	angle_increment;

	i = 0;
	mlx_clear_window(data->mlx, data->mlx_new_window);
	update_position(data);
	data->player.rotation_angle = \
	nornmalize_any_angle(data->player.rotation_angle);
	angle_increment = (FOV) / (NUM_RAYS);
	angle = data->player.rotation_angle - ((FOV) / 2);
	draw_rect(data, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2, 0x0);
	draw_rect(data, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, \
	WINDOW_HEIGHT - (WINDOW_HEIGHT / 2), 0x054d14);
	while (i < (NUM_RAYS))
	{
		data->ray[i] = (t_ray){0};
		draw_all_lines(data, i, nornmalize_any_angle(angle));
		angle += angle_increment;
		i++;
	}
	render_3d(data);
	draw_scene(data);
	draw_player(data);
	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line_dda(data, FACTOR * data->player.x, FACTOR * data->player.y, \
		FACTOR * data->ray[i].the_x_wallhit, \
		FACTOR * data->ray[i].the_y_wallhit, 0xfc6500);
		i++;
	}
	draw_line_dda(data, FACTOR * (data->player.x), \
	FACTOR * (data->player.y), FACTOR * \
	(data->player.x + cos(data->player.rotation_angle) * 30), \
	FACTOR * (data->player.y + \
	sin(data->player.rotation_angle) * 30), 0xfcdb03);
	mlx_put_image_to_window(data->mlx, \
	data->mlx_new_window, data->img_ptr, 0, 0);
	return (0);
}

int main()
{
	t_data	data;
	int		tmp;

	char map[11][15] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', 'S', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '1', '1', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

	data.player = (t_player){.x = WINDOW_WIDTH / 2, \
	.y = WINDOW_HEIGHT / 2, .move_step = 0, \
	.speed = 0.5, .turn_direction = 0, \
	.walk_direction = 0, .flag = 0, \
	.rotation_angle = PI / 2, .rotation_speed = 5 * (PI / 180)};
	data.offset = (t_textures){0};
	// data.draw = (t_draw){0};
	data.mlx = mlx_init();
	data.mlx_new_window = mlx_new_window(data.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "USM4");
	data.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr_ptr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel,
			&data.size_line, &data.endian);
	cpy_map(&data, map);
	if (!mlx_hook(data.mlx_new_window, 2, 0, handle_keypress, &data))
		return ((perror("mlx hook failure")), 1);
	if (!mlx_hook(data.mlx_new_window, 3, 0, handle_keyrelease, &data))
		return ((perror("mlx hook failure")), 1);
	if (!mlx_hook(data.mlx_new_window, 17, 0, quit_window, &data))
		return ((perror("mlx hook failure")), 1);
	data.textures[0].n_img = mlx_xpm_file_to_image(data.mlx, \
	"assets/wall.xpm", &data.textures[0].width, &data.textures[0].height);
	data.textures[1].s_img = mlx_xpm_file_to_image(data.mlx, \
	"assets/wall1.xpm", &data.textures[1].width, &data.textures[1].height);
	data.textures[2].e_img = mlx_xpm_file_to_image(data.mlx, \
	"assets/wall2.xpm", &data.textures[2].width, &data.textures[2].height);
	data.textures[3].w_img = mlx_xpm_file_to_image(data.mlx, \
	"assets/wall3.xpm", &data.textures[3].width, &data.textures[3].height);
	data.textures[0].arr = (uint32_t *)mlx_get_data_addr(data. \
	textures[0].n_img, &tmp, &tmp, &tmp);
	data.textures[1].arr = (uint32_t *)mlx_get_data_addr(data. \
	textures[1].s_img, &tmp, &tmp, &tmp);
	data.textures[2].arr = (uint32_t *)mlx_get_data_addr(data. \
	textures[2].e_img, &tmp, &tmp, &tmp);
	data.textures[3].arr = (uint32_t *)mlx_get_data_addr(data. \
	textures[3].w_img, &tmp, &tmp, &tmp);
	mlx_loop_hook(data.mlx, update_render, &data);
	mlx_loop(data.mlx);
}
