/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:14:29 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/17 03:49:14 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_map_wall(char **virtual_map, t_dimention dmt)
{
	while (virtual_map[dmt.i])
	{
		dmt.j = 0;
		while (virtual_map[dmt.i][dmt.j])
		{
			if ((virtual_map[dmt.i][dmt.j] == '0'
				|| virtual_map[dmt.i][dmt.j] == get_start_point(virtual_map))
				&& (virtual_map[dmt.i + 1][dmt.j] == ' '
				|| virtual_map[dmt.i - 1][dmt.j] == ' '
				|| virtual_map[dmt.i][dmt.j + 1] == ' '
				|| virtual_map[dmt.i][dmt.j - 1] == ' '))
				display_errors2(707);
			dmt.j++;
		}
		dmt.i++;
	}
}

char	**parse_rgb_colors(t_dimention *dmt, char *rgb_colors)
{
	char	**rgb;

	if (dmt->flag != 2)
		display_errors3(-404);
	rgb = ft_split_prs(rgb_colors, ',');
	dmt->i = 0;
	while (rgb[dmt->i])
	{
		dmt->j = 0;
		while (rgb[dmt->i][dmt->j] && rgb[dmt->i][dmt->j] == ' ')
			dmt->j++;
		while (rgb[dmt->i][dmt->j] && ft_isdigit(rgb[dmt->i][dmt->j]) == 1)
			dmt->j++;
		if (rgb[dmt->i][dmt->j] && rgb[dmt->i][dmt->j] == ' ')
		{
			while (rgb[dmt->i][dmt->j] && rgb[dmt->i][dmt->j] == ' ')
				dmt->j++;
			if (rgb[dmt->i][dmt->j] != '\0')
				display_errors3(-404);
		}
		dmt->i++;
	}
	return (rgb);
}

char	**check_rgb_colors(char *rgb_colors)
{
	t_dimention	dmt;
	char		**rgb;

	dmt.j = 0;
	dmt.i = 0;
	dmt.flag = 0;
	while (rgb_colors[dmt.j])
	{
		if (rgb_colors[dmt.j] != ' ' && rgb_colors[dmt.j] != ','
			&& ft_isdigit(rgb_colors[dmt.j]) == 0)
			display_errors3(-404);
		if (rgb_colors[dmt.j] == ',')
			dmt.flag++;
		dmt.j++;
	}
	rgb = parse_rgb_colors(&dmt, rgb_colors);
	dmt.j = -1;
	while (rgb[++dmt.j])
		if (!(ft_atoi_prs(rgb[dmt.j]) >= 0 && ft_atoi_prs(rgb[dmt.j]) <= 255))
			display_errors3(-404);
	if (dmt.j != 3)
		display_errors3(-404);
	return (rgb);
}

void	which_element(t_elements *elmt, t_dimention *dmt)
{
	char	identifier;

	if (check_for_each_element(elmt->tmp, dmt) == 0)
	{
		identifier = elmt->tmp[dmt->j];
		if (elmt->tmp[dmt->j + 2] == ' ')
		{
			pointer_plus_index(elmt, dmt, 2);
			set_element_data(elmt->tmp, elmt, identifier);
		}
		else if (elmt->tmp[dmt->j + 1] == ' ')
		{
			pointer_plus_index(elmt, dmt, 1);
			set_element_data(elmt->tmp, elmt, identifier);
		}
	}
	else if (check_for_each_element(elmt->tmp, dmt) == 1)
		display_errors2(-101);
}

t_f_c_colors	parse_map_elements(t_elements *elmt,
					t_dimention *dmt, char *mc_1d)
{
	t_f_c_colors	fcc;

	check_textures_path(elmt);
	check_empty_lines(mc_1d, dmt->skip_elements);
	fcc.floor_rgb = check_rgb_colors(elmt->floor_color);
	fcc.ceiling_rgb = check_rgb_colors(elmt->ceiling_color);
	return (fcc);
}
