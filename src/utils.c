/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 00:19:17 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/06 01:23:45 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return;
	dst = data->addr_ptr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_rect(t_data *data, double x, double y, double width, double height, int color)
{
	int i;
	int j;

	i = y;
	while (i < y + height)
	{
		j = x;
		while (j < x + width)
		{
			my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

int my_own_round(double num)
{
	double fractional_part;

	fractional_part = num - (int)num;
	if (fractional_part >= 0.5)
		return ((int)(num + 1.0));
	else
		return ((int)num);
}

int my_own_abs(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

char **allocate_the_map()
{
	char **cpy;
	int i;

	i = 0;
	cpy = malloc(sizeof(char *) * (NUM_ROWS + 1));
	if (!cpy)
	{
		perror("MALLOC FAILURE");
		exit(1);
	}
	while (i < NUM_ROWS)
	{
		cpy[i] = malloc(sizeof(char) * (NUM_COLS + 1));
		if (!cpy[i])
		{
			perror("MALLOC FAILURE");
			exit(1);
		}
		i++;
	}
	return (cpy);
}

void cpy_map(t_data *data, char map[NUM_ROWS][NUM_COLS])
{
	int i;
	int j;

	i = 0;
	data->map = allocate_the_map();
	while (i < NUM_ROWS)
	{
		j = 0;
		while (j < NUM_COLS)
		{

			data->map[i][j] = map[i][j];
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
	data->map[i] = NULL;
}
