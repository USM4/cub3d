/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 01:20:11 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/12 18:38:49 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void parsing(char **map_code, char **virtual_map)
{
	t_dimention dmt;
	
	dmt = check_map_elements(map_code);
	check_map_characters(map_code, dmt);
	check_map_4sides_wall(virtual_map, dmt);
	check_map_wall(virtual_map, dmt);	
}

void lol()
{
	system("leaks parsing");
}

int main(int ac, char **av)
{
	char **map_code;
	char **virtual_map;
	int fd;
	// atexit(lol);
	if (ac < 2)
		display_errors(303);
	check_map_extension(av);
	fd = open(av[1], O_CREAT | O_RDONLY);
	if (fd == -1)
		display_errors(404);
	map_code = join_map_code(fd);
	virtual_map = create_virtual_map(map_code);
	parsing(map_code, virtual_map);
	// check_map_elements(map_code);
	// printf("\n---------------------------------------------------------------------\n");
	// while (*map_code)//map
	// 	printf("[%s]\n", *map_code++);
}