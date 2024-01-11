/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 01:20:11 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/09 04:49:15 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"


int main(int ac, char **av)
{
	if (ac < 2)
		display_errors(303);
	check_map_extension(av);
	int fd = open(av[1], O_CREAT | O_RDONLY);
	if (fd == -1)
		display_errors(404);
	char **mc = join_map_code(fd);
	check_map_elements(mc);
	// check_map_characters(mc);
	// char **vm = create_virtual_map(mc);
	// check_map_4sides_wall(vm);
	// check_map_wall(vm);
	
	// printf("\n---------------------------------------------------------------------\n");
	// while (*mc)//map
	// 	printf("[%s]\n", *mc++);
}