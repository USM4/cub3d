/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:29:04 by oredoine          #+#    #+#             */
/*   Updated: 2024/01/10 16:13:46 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_own_round(double num)
{
	double	fractional_part;

	fractional_part = num - (int)num;
	if (fractional_part >= 0.5)
		return ((int)(num + 1.0));
	else
		return ((int)num);
}

int	my_own_abs(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}