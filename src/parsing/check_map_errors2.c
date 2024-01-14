/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:24:07 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/14 18:32:00 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void which_element(char **element, char *texture_path)
{
		if (*element != NULL)
			display_errors2(909);
		*element = texture_path;
}

void set_element_data(char *texture_path, t_elements *elmt, char identifier)
{
	
	if (identifier == 'N')
		which_element(&elmt->no_path, texture_path);
	else if (identifier == 'S')
		which_element(&elmt->so_path, texture_path);
	else if (identifier == 'W')
		which_element(&elmt->we_path, texture_path);
	else if (identifier == 'E')
		which_element(&elmt->ea_path, texture_path);
	else if (identifier == 'F')
		which_element(&elmt->floor_color, texture_path);
	else if (identifier == 'C')
		which_element(&elmt->ceiling_color, texture_path);
		
}

void pointer_plus_index(t_elements *elmt, t_dimention *dmt, int space_index)
{
	if (elmt->tmp[dmt->j + space_index] == ' ')
	{
		dmt->j += space_index;
		while (elmt->tmp[dmt->j] == ' ')
			dmt->j++;
		elmt->tmp = elmt->tmp + dmt->j;
		while (elmt->tmp[dmt->j] != '\0')
			dmt->j++;
		dmt->j--;
		while (elmt->tmp[dmt->j] == ' ')
			dmt->j--;
		elmt->tmp[dmt->j + 1] = '\0';
	}
}

int check_pointer_state(t_elements *elmt)
{
	if (!elmt->no_path || !elmt->so_path || !elmt->we_path || !elmt->ea_path
		|| !elmt->floor_color || !elmt->ceiling_color)
			return (-1);
	else if (elmt->no_path && elmt->so_path && elmt->we_path && elmt->ea_path
		&& elmt->floor_color && elmt->ceiling_color)
			return (1);
	return (0);
	
}

int check_for_each_element(char *map_content, t_dimention *dmt)
{
	 if ((map_content[dmt->j] == 'N' && map_content[dmt->j + 1] == 'O')
		|| (map_content[dmt->j] == 'S' && map_content[dmt->j + 1] == 'O')
		|| (map_content[dmt->j] == 'W' && map_content[dmt->j + 1] == 'E')
		|| (map_content[dmt->j] == 'E' && map_content[dmt->j + 1] == 'A')
		|| (map_content[dmt->j] == 'F' && map_content[dmt->j + 1] == ' ')
		|| (map_content[dmt->j] == 'C' && map_content[dmt->j + 1] == ' '))
			return (0);
	else
		return(1);
	return (-1);
}

void check_textures_path(t_elements *elmt)
{
	if (elmt->no_path[0] == '\0' || elmt->so_path[0] == '\0' || elmt->we_path[0] == '\0' || elmt->ea_path[0] == '\0'
		|| elmt->floor_color[0] == '\0' || elmt->ceiling_color[0] == '\0')
			display_errors3(-202);
}

void check_empty_lines(char *mc_1d, int skip_elements)
{
	t_dimention dmt;
	int new_lines;

	dmt.j = 0;
	dmt.flag = 0;
	new_lines = 0;
	while(mc_1d[dmt.j])
	{
		if ((mc_1d[dmt.j] == 'N' && mc_1d[dmt.j + 1] == 'O')
		|| (mc_1d[dmt.j] == 'S' && mc_1d[dmt.j + 1] == 'O')
		|| (mc_1d[dmt.j] == 'W' && mc_1d[dmt.j + 1] == 'E')
		|| (mc_1d[dmt.j] == 'E' && mc_1d[dmt.j + 1] == 'A')
		|| (mc_1d[dmt.j] == 'F' && mc_1d[dmt.j + 1] == ' ')
		|| (mc_1d[dmt.j] == 'C' && mc_1d[dmt.j + 1] == ' '))
			dmt.flag++;
		if (mc_1d[dmt.j] == '\n' && mc_1d[dmt.j + 1] == '\n')
			new_lines++;
		if (dmt.flag == 6)
			break;
		dmt.j++;
	}
	dmt.j = skip_elements + new_lines;
	while(mc_1d[dmt.j] == '\n')
		dmt.j++;
	// printf("%c\n", mc_1d[dmt.j]);
	// printf("%d\n", new_lines);
	while(mc_1d[dmt.j])
	{
		if (mc_1d[dmt.j] == '\n' && mc_1d[dmt.j + 1] == '\n')
			display_errors2(808);
		dmt.j++;
	}
}

void check_rgb_colors(char *rgb_colors)
{
	t_dimention dmt;
	f_c_colors fcc;

	dmt.j = 0;
	dmt.i = 0;
	dmt.flag = 0;
	while(rgb_colors[dmt.j])
	{
		if (rgb_colors[dmt.j] != ' ' && rgb_colors[dmt.j] != ','
			&& ft_isdigit(rgb_colors[dmt.j]) == 0)
				display_errors3(-404);
		if (rgb_colors[dmt.j] == ',')
			dmt.flag++;
		dmt.j++;
	}
	if (dmt.flag != 2)
		display_errors3(-404);
	fcc.floor_ceiling_rgb = ft_split_prs(rgb_colors, ',');
	dmt.i = 0;
	while (fcc.floor_ceiling_rgb[dmt.i])
	{
		dmt.j = 0;
		while (fcc.floor_ceiling_rgb[dmt.i][dmt.j] && fcc.floor_ceiling_rgb[dmt.i][dmt.j] == ' ')
			dmt.j++;
		while (fcc.floor_ceiling_rgb[dmt.i][dmt.j] && ft_isdigit(fcc.floor_ceiling_rgb[dmt.i][dmt.j]) == 1)
			dmt.j++;
		if (fcc.floor_ceiling_rgb[dmt.i][dmt.j] && fcc.floor_ceiling_rgb[dmt.i][dmt.j] == ' ')
		{
			while (fcc.floor_ceiling_rgb[dmt.i][dmt.j] && fcc.floor_ceiling_rgb[dmt.i][dmt.j] == ' ')
				dmt.j++;
			if (fcc.floor_ceiling_rgb[dmt.i][dmt.j] != '\0')
				display_errors3(-404);
		}
		dmt.i++;
	}
	dmt.i = 0;
	dmt.j = 0;
	while (fcc.floor_ceiling_rgb[dmt.j])
	{
		if (!(ft_atoi_prs(fcc.floor_ceiling_rgb[dmt.j]) >= 0 && ft_atoi_prs(fcc.floor_ceiling_rgb[dmt.j]) <= 255))
				display_errors3(-404);
		else
			fcc.rgb_range[dmt.i++] = ft_atoi_prs(fcc.floor_ceiling_rgb[dmt.j]);
		dmt.j++;
	}
	if (dmt.j != 3)
		display_errors3(-404);
}

t_dimention  check_map_elements(char **map_content, char *mc_1d)
{
	t_dimention dmt;
	t_elements elmt;
	char identifier;
	int skip_elements;

	elmt.no_path = NULL;
	elmt.so_path = NULL;
	elmt.we_path = NULL;
	elmt.ea_path = NULL;
	elmt.floor_color = NULL;
	elmt.ceiling_color = NULL;
	dmt = get_mc_dimentios(map_content);
	elmt.tmp = NULL;
	dmt.i = 0;
	skip_elements = 0;
	while (map_content[dmt.i])
	{
		elmt.tmp = map_content[dmt.i];
		skip_elements += ft_strlen_prs(map_content[dmt.i]) + 1;
		dmt.j = 0;
		while (elmt.tmp[dmt.j] == ' ')
			dmt.j++;
		if (check_for_each_element(elmt.tmp, &dmt) == 0)
		{
			identifier = elmt.tmp[dmt.j];
			if (elmt.tmp[dmt.j + 2] == ' ')
			{
				pointer_plus_index(&elmt, &dmt, 2);
				set_element_data(elmt.tmp, &elmt, identifier);
			}
			else if (elmt.tmp[dmt.j + 1] == ' ')
			{
				pointer_plus_index(&elmt, &dmt, 1);
				set_element_data(elmt.tmp, &elmt, identifier);
			}
		}
		else if (check_for_each_element(elmt.tmp, &dmt) == 1)
			display_errors2(-101);
		if (check_pointer_state(&elmt) == 1)
		{
			dmt.j = 0;
			dmt.i++;
			break;
		}
		dmt.i++;
	}
	if (check_pointer_state(&elmt) == -1)
		display_errors2(-101);
	check_textures_path(&elmt);
	check_empty_lines(mc_1d, skip_elements);
	check_rgb_colors(elmt.floor_color);
	check_rgb_colors(elmt.ceiling_color);


	// printf("[%s]\n", elmt.no_path);
	// printf("[%s]\n", elmt.so_path);
	// printf("[%s]\n", elmt.we_path);
	// printf("[%s]\n", elmt.ea_path);
	// printf("[%s]\n", elmt.floor_color);
	// printf("[%s]\n", elmt.ceiling_color);
	return(dmt);
}
