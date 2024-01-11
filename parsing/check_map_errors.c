/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 04:36:06 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/08 01:05:38 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void	check_map_extension(char **av)
{
	int j;

	j = 0;
	while (av[1][j])
		j++;
	if (av[1][j - 1] == 'b' && av[1][j - 2] == 'u'
		&& av[1][j - 3] == 'c' && av[1][j - 4] == '.')
			return;
	else
		display_errors(101);
}

void	check_map_characters(char **map_code)
{
	t_dimention dmt;

	dmt.flag = 0;
	dmt.i = 0;
	while (map_code[dmt.i])
	{
		dmt.j = 0;
		while (map_code[dmt.i][dmt.j])
		{
			if (map_code[dmt.i][dmt.j] != '0' && map_code[dmt.i][dmt.j] != '1'
				&& map_code[dmt.i][dmt.j] != 'N' && map_code[dmt.i][dmt.j] != 'S'
				&& map_code[dmt.i][dmt.j] != 'E' && map_code[dmt.i][dmt.j] != 'W'
				&& map_code[dmt.i][dmt.j] != ' ')
					display_errors(505);
			if (map_code[dmt.i][dmt.j] =='N' || map_code[dmt.i][dmt.j] =='S'
				|| map_code[dmt.i][dmt.j] =='E' || map_code[dmt.i][dmt.j] =='W')
					dmt.flag++;
			dmt.j++;
		}
		dmt.i++;
	}
	if (dmt.flag != 1)
		display_errors2(606);
}


char	**create_virtual_map(char **map_code)
{
	t_dimention dmt;
	char **virtual_map;
	
	dmt = get_mc_dimentios(map_code);
	dmt.i = 0;
	virtual_map = malloc((dmt.lines + 1) * sizeof(char *));
	virtual_map[dmt.lines] = NULL;
	dmt.lines--;
	while (dmt.lines >= 0)
	{
		virtual_map[dmt.lines] = malloc((dmt.longest_line + 1) * sizeof(char));
		dmt.lines--;
	}
	while (map_code[dmt.i])
	{
		dmt.j = 0;
		while (map_code[dmt.i][dmt.j])
		{
			virtual_map[dmt.i][dmt.j] = map_code[dmt.i][dmt.j];
			dmt.j++;
		}
		virtual_map[dmt.i][dmt.longest_line] = '\0';
		while (dmt.j < dmt.longest_line)
		{
			virtual_map[dmt.i][dmt.j] = ' ';
			dmt.j++;
		}
		dmt.i++;
	}
	return (virtual_map);
}

void	check_map_4sides_wall(char **virtual_map)
{
	t_dimention dmt;

	dmt = get_mc_dimentios(virtual_map);
	dmt.i = 0;
	while (dmt.i < dmt.lines)
	{
		if ((virtual_map[dmt.i][0] != '1' && virtual_map[dmt.i][0] != ' ')
			|| (virtual_map[dmt.i][dmt.longest_line - 1] != '1'
				&& virtual_map[dmt.i][dmt.longest_line - 1] != ' '))
					display_errors2(707);
		dmt.j = 0;
		while (dmt.j < dmt.longest_line)
		{
			if ((virtual_map[0][dmt.j] != '1' && virtual_map[0][dmt.j] != ' ')
				|| (virtual_map[dmt.lines - 1][dmt.j] != '1'
					&& virtual_map[dmt.lines - 1][dmt.j] != ' '))
						display_errors2(707);
			dmt.j++;
		}
		dmt.i++;
	}
}


void	check_map_wall(char **virtual_map)
{
	t_dimention dmt;

	dmt = get_mc_dimentios(virtual_map);
	dmt.i = 0;
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
