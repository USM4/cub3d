/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:24:48 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/12 17:31:02 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

char	**join_map_code(int fd)
{
	char	**map_code;
	char	*mc_1d;
	char	buf[2];
	int		i;
	int		j;

	i = read(fd, buf, 1);
	if (i == 0)
		display_errors(202);
	j = 0;
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
	map_code = ft_split_prs(mc_1d, '\n');
	return (free(mc_1d), map_code);
}


char get_start_point(char **map_code)
{
	int	i;
	int	j;
	char start_point;

	i = 0;
	while (map_code[i])
	{
		j = 0;
		while (map_code[i][j])
		{
			if ((map_code[i][j] == 'N' && (map_code[i][j + 1] == '0' || map_code[i][j + 1] == '1'))
				|| (map_code[i][j] == 'S' && (map_code[i][j + 1] == '0' || map_code[i][j + 1] == '1'))
				|| (map_code[i][j] == 'W' && (map_code[i][j + 1] == '0' || map_code[i][j + 1] == '1'))
				|| (map_code[i][j] == 'E' && (map_code[i][j + 1] == '0' || map_code[i][j + 1] == '1'))) 
			{
				start_point = map_code[i][j]; 
				return (start_point);
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_dimention	get_mc_dimentios(char **map_code)
{
	t_dimention dmt;

	dmt.i = 0;
	dmt.longest_line = 0;
	while (map_code[dmt.i])
	{
		dmt.j = 0;
		while (map_code[dmt.i][dmt.j])
			dmt.j++;
		if (dmt.j > dmt.longest_line)
			dmt.longest_line = dmt.j;
		dmt.i++;
	}
	dmt.lines = dmt.i;
	// printf("---------------[%d]------------\n", dmt.lines);
	return (dmt);
}


