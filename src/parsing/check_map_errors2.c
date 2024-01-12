/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlabouit <hlabouit@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:24:07 by hlabouit          #+#    #+#             */
/*   Updated: 2024/01/12 17:16:45 by hlabouit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parsing.h"

void which_element(char **element, char *texture_path)
{
        if (*element != NULL)
            display_errors2(909);
        *element = texture_path;
        // printf("%s\n", element);
        // printf("%s\n", texture_path);
}

void set_element_data(char *texture_path, t_elements *elmt, char identifier)
{
    
    if (identifier == 'N')
        which_element(&elmt->no_path, texture_path);
    else if (identifier == 'S')
        which_element(&elmt->so_path, texture_path);
    else if (identifier == 'W')
        which_element(&elmt->we_path, texture_path);
    else if (identifier == 'E')
        which_element(&elmt->ea_path, texture_path);
    else if (identifier == 'F')
        which_element(&elmt->floor_color, texture_path);
    else if (identifier == 'C')
        which_element(&elmt->ceiling_color, texture_path);
        
}

void pointer_plus_index(t_elements *elmt, t_dimention *dmt, int space_index)
{
    if (elmt->tmp[dmt->j + space_index] == ' ')
    {
        dmt->j += space_index;
        while (elmt->tmp[dmt->j] == ' ')
            dmt->j++;
        elmt->tmp = elmt->tmp + dmt->j;
        while (elmt->tmp[dmt->j] != '\0')
            dmt->j++;
        dmt->j--;
        while (elmt->tmp[dmt->j] == ' ')
            dmt->j--;
        elmt->tmp[dmt->j + 1] = '\0';
    }
}

int check_pointer_state(t_elements *elmt)
{
    if (!elmt->no_path || !elmt->so_path || !elmt->we_path || !elmt->ea_path
		|| !elmt->floor_color || !elmt->ceiling_color)
            return (-1);
    else if (elmt->no_path && elmt->so_path && elmt->we_path && elmt->ea_path
		&& elmt->floor_color && elmt->ceiling_color)
            return (1);
    return (0);
    
}

int check_for_each_element(char *map_code, t_dimention *dmt)
{
     if ((map_code[dmt->j] == 'N' && map_code[dmt->j + 1] == 'O')
        || (map_code[dmt->j] == 'S' && map_code[dmt->j + 1] == 'O')
        || (map_code[dmt->j] == 'W' && map_code[dmt->j + 1] == 'E')
        || (map_code[dmt->j] == 'E' && map_code[dmt->j + 1] == 'A')
        || (map_code[dmt->j] == 'F' && map_code[dmt->j + 1] == ' ')
        || (map_code[dmt->j] == 'C' && map_code[dmt->j + 1] == ' '))
            return (0);
    else if (map_code[0] != '\0')
        return(1);
    return (-1);
}

t_dimention  check_map_elements(char **map_code)
{
    t_dimention dmt;
    t_elements elmt;
    char identifier;

    elmt.no_path = NULL;
    elmt.so_path = NULL;
    elmt.we_path = NULL;
    elmt.ea_path = NULL;
    elmt.floor_color = NULL;
    elmt.ceiling_color = NULL;
    dmt = get_mc_dimentios(map_code);
    elmt.tmp = NULL;
    dmt.i = 0;
    while (map_code[dmt.i])
    {
        elmt.tmp = map_code[dmt.i];
        dmt.j = 0;
        while (elmt.tmp[dmt.j] == ' ')
            dmt.j++;
        if (check_for_each_element(elmt.tmp, &dmt) == 0)
        {
            identifier = elmt.tmp[dmt.j];
            if (elmt.tmp[dmt.j + 2] == ' ')
            {
                pointer_plus_index(&elmt, &dmt, 2);
                set_element_data(elmt.tmp, &elmt, identifier);
            }
            else if (elmt.tmp[dmt.j + 1] == ' ')
            {
                pointer_plus_index(&elmt, &dmt, 1);
                set_element_data(elmt.tmp, &elmt, identifier);
            }
        }
        else if (check_for_each_element(elmt.tmp, &dmt) == 1)
            display_errors3(479);
        if (check_pointer_state(&elmt) == 1)
        {
            //move to next line where all empty lines skipped and remmoved in split 
            dmt.j = 0;
            dmt.i++;
            // printf("bachkharej%d\n", dmt.i);
            // exit(0);
            return (dmt);
        }
        dmt.i++;
    }
    if (check_pointer_state(&elmt) == -1)
        display_errors3(777);
    // printf("[%s]\n", elmt.no_path);
    // printf("[%s]\n", elmt.so_path);
    // printf("[%s]\n", elmt.we_path);
    // printf("[%s]\n", elmt.ea_path);
    // printf("[%s]\n", elmt.floor_color);
    // printf("[%s]\n", elmt.ceiling_color);
    // exit(0);
    return(dmt);
}
