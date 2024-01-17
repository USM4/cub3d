/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:24:45 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/17 04:01:54 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	display_errors(int signal)
{
	if (signal == 101)
	{
		printf("Error\ninvalid map file extension!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == 202)
	{
		printf("Error\nmap file is empty!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == 303)
	{
		printf("Error\ninvalid number of arguments!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == 404)
	{
		printf("Error\nfailed to open map file!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == 505)
	{
		printf("Error\ninvalid map code characters!\n");
		exit(EXIT_FAILURE);
	}
}

void	display_errors2(int signal)
{
	if (signal == 606)
	{
		printf("Error\nmap code must countain one single start point!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == 707)
	{
		printf("Error\nmap code isn't surrounded by walls!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == 808)
	{
		printf("Error\nmap code countains empty lines!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == 909)
	{
		printf("Error\nmap file countains duplicated element!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == -101)
	{
		printf("Error\nmap file must countain 6 valid elements at the top!\n");
		exit(EXIT_FAILURE);
	}
}

void	display_errors3(int signal)
{
	if (signal == -202)
	{
		printf("Error\nelements must provide data!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == -303)
	{
		printf("Error\nstart point must be surrounded by walls!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == -404)
	{
		printf("Error\nfloor and ceiling RGB colors must composed \
of 3 numerical values of this range [0,255]!\n");
		exit(EXIT_FAILURE);
	}
	if (signal == -505)
	{
		printf("Error\nmlx hook failed!\n");
		exit(EXIT_FAILURE);
	}
}
