/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:28:08 by oredoine          #+#    #+#             */
/*   Updated: 2023/12/09 01:26:47 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <mlx.h>
#include <unistd.h>

#define TILE_SIZE 32
#define NUM_ROWS 11
#define NUM_COLS 15 


#define WINDOW_HEIGHT TILE_SIZE * NUM_ROWS
#define WINDOW_WIDTH TILE_SIZE * NUM_COLS

typedef struct s_data {

	void			*mlx_new_window;
	void			*mlx;

}	t_data;




#endif