/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:09:05 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/17 02:47:21 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_empty_lines(char *mc_1d, int skip_elements)
{
	t_dimention	dmt;
	int			new_lines;

	dmt.j = 0;
	dmt.flag = 0;
	new_lines = 0;
	while (mc_1d[dmt.j])
	{
		if (check_for_identifiers(mc_1d, &dmt) == 1)
			dmt.flag++;
		if (mc_1d[dmt.j] == '\n' && mc_1d[dmt.j + 1] == '\n')
			new_lines++;
		if (dmt.flag == 6)
			break ;
		dmt.j++;
	}
	dmt.j = skip_elements + new_lines;
	while (mc_1d[dmt.j] == '\n')
		dmt.j++;
	while (mc_1d[dmt.j])
	{
		if (mc_1d[dmt.j] == '\n' && mc_1d[dmt.j + 1] == '\n')
			display_errors2(808);
		dmt.j++;
	}
}

int	check_for_identifiers(char *map_content, t_dimention *dmt)
{
	if ((map_content[dmt->j] == 'N' && map_content[dmt->j + 1] == 'O')
		|| (map_content[dmt->j] == 'S' && map_content[dmt->j + 1] == 'O')
		|| (map_content[dmt->j] == 'W' && map_content[dmt->j + 1] == 'E')
		|| (map_content[dmt->j] == 'E' && map_content[dmt->j + 1] == 'A')
		|| (map_content[dmt->j] == 'F' && map_content[dmt->j + 1] == ' ')
		|| (map_content[dmt->j] == 'C' && map_content[dmt->j + 1] == ' '))
		return (1);
	return (-1);
}

int	check_for_each_element(char *map_content, t_dimention *dmt)
{
	if (check_for_identifiers(map_content, dmt) == 1)
		return (0);
	else
		return (1);
	return (-1);
}

void	check_textures_path(t_elements *elmt)
{
	if (elmt->no_path[0] == '\0' || elmt->so_path[0] == '\0'
		|| elmt->we_path[0] == '\0' || elmt->ea_path[0] == '\0'
		|| elmt->floor_color[0] == '\0' || elmt->ceiling_color[0] == '\0')
		display_errors3(-202);
}

void	set_pointers_to_null(t_elements *elmt,
			t_dimention *dmt, char **map_content)
{
	elmt->no_path = NULL;
	elmt->so_path = NULL;
	elmt->we_path = NULL;
	elmt->ea_path = NULL;
	elmt->floor_color = NULL;
	elmt->ceiling_color = NULL;
	*dmt = get_mc_dimentios(map_content);
	elmt->tmp = NULL;
	dmt->i = 0;
	dmt->skip_elements = 0;
}
