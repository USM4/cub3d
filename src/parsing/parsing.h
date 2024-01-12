/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:19:54 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/09 17:08:58 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include<libc.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <fcntl.h>

typedef struct t_elements
{
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	char *ceiling_color;
	char *floor_color;
	char *tmp;
	int		index;
}t_elements;

typedef struct t_dimention
{
	int		lines;
	int		longest_line;
	int		i;
	int		j;
	int		flag;
}t_dimention;


char		**join_map_code(int fd);
void		check_map_extension(char **av);
void		check_map_characters(char **map_code);
void		check_map_wall(char **virtual_map);
void		check_map_4sides_wall(char **virtual_map);
char		get_start_point(char **map_code);
t_dimention	get_mc_dimentios(char **map_code);
char		**create_virtual_map(char **map_code);
void    check_map_elements(char **map_code);
void set_element_data(char *texture_path, t_elements *elmt, char identifier);
void		display_errors(int signal);
void		display_errors2(int signal);

///////// libft //////////
int		ft_strlen_prs(char *s);
size_t	ft_strlcpy_prs(char *dst, char *src, size_t dstsize);
char	*ft_strjoin_prs(char *s1, char *s2);
char	**ft_split_prs(char *s, char c);
char	*ft_strdup_prs(char *s1);
///////// libft //////////


#endif