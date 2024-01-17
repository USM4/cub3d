/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:24:07 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/17 02:59:33 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	assign_element(char **element, char *texture_path)
{
	if (*element != NULL)
		display_errors2(909);
	*element = texture_path;
}

void	set_element_data(char *texture_path, t_elements *elmt, char identifier)
{
	if (identifier == 'N')
		assign_element(&elmt->no_path, texture_path);
	else if (identifier == 'S')
		assign_element(&elmt->so_path, texture_path);
	else if (identifier == 'W')
		assign_element(&elmt->we_path, texture_path);
	else if (identifier == 'E')
		assign_element(&elmt->ea_path, texture_path);
	else if (identifier == 'F')
		assign_element(&elmt->floor_color, texture_path);
	else if (identifier == 'C')
		assign_element(&elmt->ceiling_color, texture_path);
}

void	pointer_plus_index(t_elements *elmt, t_dimention *dmt, int space_index)
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

int	check_pointer_state(t_elements *elmt)
{
	if (!elmt->no_path || !elmt->so_path || !elmt->we_path || !elmt->ea_path
		|| !elmt->floor_color || !elmt->ceiling_color)
		return (-1);
	else if (elmt->no_path && elmt->so_path && elmt->we_path && elmt->ea_path
		&& elmt->floor_color && elmt->ceiling_color)
		return (1);
	return (0);
}

t_elements	check_map_elements(char **map_content, char *mc_1d)
{
	t_dimention	dmt;
	t_elements	elmt;

	set_pointers_to_null(&elmt, &dmt, map_content);
	while (map_content[dmt.i])
	{
		elmt.tmp = map_content[dmt.i];
		dmt.skip_elements += ft_strlen_prs(map_content[dmt.i]) + 1;
		dmt.j = 0;
		while (elmt.tmp[dmt.j] == ' ')
			dmt.j++;
		which_element(&elmt, &dmt);
		if (check_pointer_state(&elmt) == 1)
		{
			dmt.j = 0;
			dmt.i++;
			break ;
		}
		dmt.i++;
	}
	if (check_pointer_state(&elmt) == -1)
		display_errors2(-101);
	elmt.fcc = parse_map_elements(&elmt, &dmt, mc_1d);
	elmt.dmt = dmt;
	return (elmt);
}
