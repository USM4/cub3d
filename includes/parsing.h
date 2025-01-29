/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oredoine <oredoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 00:19:54 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/17 11:26:43 by oredoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H   
# define PARSING_H

# include <libc.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <fcntl.h>

typedef struct t_dimention
{
	int				fd;
	int				lines;
	int				longest_line;
	int				i;
	int				j;
	int				flag;
	int				skip_elements;
}	t_dimention;

typedef struct t_f_c_colors
{
	char	**floor_rgb;
	char	**ceiling_rgb;
}	t_f_c_colors;

typedef struct t_elements
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	char			*ceiling_color;
	char			*floor_color;
	char			*tmp;
	char			**map_code;
	char			**map_content;
	char			**virtual_map;
	t_dimention		dmt;
	t_f_c_colors	fcc;
}	t_elements;
///////// libft //////////
int				ft_strlen_prs(char *s);
size_t			ft_strlcpy_prs(char *dst, char *src, size_t dstsize);
char			*ft_strjoin_prs(char *s1, char *s2);
char			**ft_split_prs(char *s, char c);
char			*ft_strdup_prs(char *s1);
int				ft_isdigit(int c);
int				ft_atoi_prs(const char *str);
///////// libft //////////
char			*join_map_content(int fd);
void			check_map_extension(char **av);
void			check_map_characters(char **map_content, t_dimention dmt);
void			check_map_wall(char **virtual_map, t_dimention dmt);
void			check_map_4sides_wall(char **virtual_map, t_dimention dmt);
int				check_start_point_sidesnt_sides(char **map_content,
					int i, int j);
char			get_start_point(char **map_content);
t_dimention		get_mc_dimentios(char **map_content);
char			**create_virtual_map(char **map_content);
void			fill_virtual_map(char **map_content, char **virtual_map,
					t_dimention *dmt);
void			set_element_data(char *texture_path, t_elements *elmt,
					char identifier);
void			pointer_plus_index(t_elements *elmt, t_dimention *dmt,
					int space_index);
void			assign_element(char **element, char *texture_path);
int				check_pointer_state(t_elements *elmt);
int				check_for_identifiers(char *map_content, t_dimention *dmt);
int				check_for_each_element(char *map_content, t_dimention *dmt);
void			check_textures_path(t_elements *elmt);
void			check_empty_lines(char *mc_1d, int skip_elements);
void			set_pointers_to_null(t_elements *elmt, t_dimention *dmt,
					char **map_content);
t_f_c_colors	parse_map_elements(t_elements *elmt, t_dimention *dmt,
					char *mc_1d);
void			which_element(t_elements *elmt, t_dimention *dmt);
t_elements		check_map_elements(char **map_content, char *mc_1d);
char			**parse_rgb_colors(t_dimention *dmt, char *rgb_colors);
char			**check_rgb_colors(char *rgb_colors);
void			display_errors(int signal);
void			display_errors2(int signal);
void			display_errors3(int signal);
void			lightweight_memory(char **tab2d);

#endif
