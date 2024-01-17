/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 04:36:06 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/17 02:47:21 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_map_extension(char **av)
{
	int	j;

	j = 0;
	while (av[1][j])
		j++;
	if (av[1][j - 1] == 'b' && av[1][j - 2] == 'u'
		&& av[1][j - 3] == 'c' && av[1][j - 4] == '.')
		return ;
	else
		display_errors(101);
}

void	check_map_characters(char **map_content, t_dimention dmt)
{
	dmt.flag = 0;
	while (map_content[dmt.i])
	{
		dmt.j = 0;
		while (map_content[dmt.i][dmt.j])
		{
			if (map_content[dmt.i][dmt.j] != '0'
				&& map_content[dmt.i][dmt.j] != '1'
				&& map_content[dmt.i][dmt.j] != get_start_point(map_content)
				&& map_content[dmt.i][dmt.j] != ' ')
				display_errors(505);
			if (map_content[dmt.i][dmt.j] == 'N'
				|| map_content[dmt.i][dmt.j] == 'S'
				|| map_content[dmt.i][dmt.j] == 'E'
				|| map_content[dmt.i][dmt.j] == 'W')
				dmt.flag++;
			dmt.j++;
		}
		dmt.i++;
	}
	if (dmt.flag != 1)
		display_errors2(606);
}

void	fill_virtual_map(char **map_content, char **virtual_map,
			t_dimention *dmt)
{
	while (map_content[dmt->i])
	{
		dmt->j = 0;
		while (map_content[dmt->i][dmt->j])
		{
			virtual_map[dmt->i][dmt->j] = map_content[dmt->i][dmt->j];
			dmt->j++;
		}
		virtual_map[dmt->i][dmt->longest_line] = '\0';
		while (dmt->j < dmt->longest_line)
		{
			virtual_map[dmt->i][dmt->j] = ' ';
			dmt->j++;
		}
		dmt->i++;
	}
}

char	**create_virtual_map(char **map_content)
{
	t_dimention	dmt;
	char		**virtual_map;

	dmt = get_mc_dimentios(map_content);
	dmt.i = 0;
	virtual_map = malloc((dmt.lines + 1) * sizeof(char *));
	virtual_map[dmt.lines] = NULL;
	dmt.lines--;
	while (dmt.lines >= 0)
	{
		virtual_map[dmt.lines] = malloc((dmt.longest_line + 1) * sizeof(char));
		dmt.lines--;
	}
	fill_virtual_map(map_content, virtual_map, &dmt);
	return (virtual_map);
}

void	check_map_4sides_wall(char **virtual_map, t_dimention dmt)
{
	int	mc_first_line;

	mc_first_line = dmt.i;
	while (dmt.i < dmt.lines)
	{
		if ((virtual_map[dmt.i][0] != '1' && virtual_map[dmt.i][0] != ' ')
			|| (virtual_map[dmt.i][dmt.longest_line - 1] != '1'
			&& virtual_map[dmt.i][dmt.longest_line - 1] != ' '))
			display_errors2(707);
		dmt.j = 0;
		while (dmt.j < dmt.longest_line)
		{
			if ((virtual_map[mc_first_line][dmt.j] != '1'
				&& virtual_map[mc_first_line][dmt.j] != ' ')
				|| (virtual_map[dmt.lines - 1][dmt.j] != '1'
				&& virtual_map[dmt.lines - 1][dmt.j] != ' '))
				display_errors2(707);
			dmt.j++;
		}
		dmt.i++;
	}
}
