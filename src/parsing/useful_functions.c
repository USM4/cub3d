/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:24:48 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/14 08:11:30 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

char	*join_map_content(int fd)
{
	char	*mc_1d;
	char	buf[2];
	int		i;

	i = read(fd, buf, 1);
	if (i == 0)
		display_errors(202);
	buf[i] = 0;
	mc_1d = ft_strdup_prs("");
	while (i)
	{
		mc_1d = ft_strjoin_prs(mc_1d, buf);
		i = read(fd, buf, 1);
		buf[i] = 0;
		// if (mc_1d[0] == '\n'
		// 	|| (mc_1d[ft_strlen_prs(mc_1d) - 1] == '\n' && buf[0] == '\n'))
		// 	display_errors2(808);
	}
	if (mc_1d[ft_strlen_prs(mc_1d) - 1] == '\n')
		display_errors2(808);
	return (mc_1d);
}


char get_start_point(char **map_content)
{
	int	i;
	int	j;
	char start_point;

	i = 0;
	while (map_content[i])
	{
		j = 0;
		while (map_content[i][j])
		{
			if ((map_content[i][j] == 'N' && (map_content[i][j + 1] == '0' || map_content[i][j + 1] == '1'))
				|| (map_content[i][j] == 'S' && (map_content[i][j + 1] == '0' || map_content[i][j + 1] == '1'))
				|| (map_content[i][j] == 'W' && (map_content[i][j + 1] == '0' || map_content[i][j + 1] == '1'))
				|| (map_content[i][j] == 'E' && (map_content[i][j + 1] == '0' || map_content[i][j + 1] == '1'))) 
			{
				start_point = map_content[i][j]; 
				return (start_point);
			}
			j++;
		}
		i++;
	}
	display_errors3(-303);
	return (0);
}

t_dimention	get_mc_dimentios(char **map_content)
{
	t_dimention dmt;

	dmt.i = 0;
	dmt.longest_line = 0;
	while (map_content[dmt.i])
	{
		dmt.j = 0;
		while (map_content[dmt.i][dmt.j])
			dmt.j++;
		if (dmt.j > dmt.longest_line)
			dmt.longest_line = dmt.j;
		dmt.i++;
	}
	dmt.lines = dmt.i;
	return (dmt);
}


