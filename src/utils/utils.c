/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:19:17 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/14 21:01:57 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->val.window_width || y >= data->val.window_height)
		return ;
	dst = data->addr_ptr + (y * data->size_line + x * \
	(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_data *data)
{
	int	i;
	int	j;

	i = data->params.y;
	while (i < data->params.y + data->params.height)
	{
		j = data->params.x;
		while (j < data->params.x + data->params.width)
		{
			my_mlx_pixel_put(data, j, i, data->params.color);
			j++;
		}
		i++;
	}
}

char	**allocate_the_map(t_data *data)
{
	char	**cpy;
	int		i;

	i = 0;
	// printf("rows %d\n", data->bridge.num_rows);
	// exit(1);
	cpy = malloc(sizeof(char *) * (data->bridge.num_rows + 1));
	if (!cpy)
	{
		perror("MALLOC FAILURE");
		exit(1);
	}
	while (i < data->bridge.num_rows)
	{
		cpy[i] = malloc(sizeof(char) * (data->bridge.longest_line + 1));
		if (!cpy[i])
		{
			perror("MALLOC FAILURE");
			exit(1);
		}
		i++;
	}
	return (cpy);
}

void	cpy_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	data->map = allocate_the_map(data);
	while (i < data->bridge.num_rows)
	{
		j = 0;
		// printf("longest %d\n", data->bridge.longest_line);
		// exit(1);
		while (j < data->bridge.longest_line)
		{
			// puts("heeeere");
			data->map[i][j] = map[i][j];
			// printf("i : %d , j : %d, map[i][j] = [%c]\n", i, j, map[i][j]);
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
	data->map[i] = NULL;
}

int	quit_window(void)
{
	exit(0);
}
