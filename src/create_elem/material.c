/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:17:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/17 00:09:55 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool ft_str_beggin_with(char *str, char *beg)
{
    return (ft_strnstr(str, beg, ft_strlen(beg)));
}


void init_mat(t_material *mat)
{
    ft_bzero(mat, sizeof(t_material));
    mat->specular = -1;
    mat->textures.checkered = false;
    // mat->textures.bump_mapping = false;
    mat->textures.t = no_map;
    mat->reflective = 0;
}

bool set_checkerboard(t_material *mat,char *info)
{
    if (!info || (!ft_strisequal(info, "ch") && !ft_strisequal(info, "ch\n")))
        return false;
    mat->textures.checkered = true;
    return (true);   
}

bool set_bump_map_type(t_material *mat,char *info)
{
    if (!info || !ft_str_beggin_with(info, "b=") || ft_strlen(info) < 3 ||  ft_strlen(info) > 4)
        return false;
    if (info[2] == 'c')
        mat->textures.t = cliff;
    else if(info[2] == 's')
        mat->textures.t = sand;
    else if (info[2] == 't')
        mat->textures.t = terrain;
    else if (info[2] == 'a')
        mat->textures.t = tree;
    else if (info[2] == 'w')
        mat->textures.t = wood;
    else
        return (false);
    mat->textures.normap = get_map_from_type(mat->textures.t);
    // mat->textures.bump_mapping = true;
    return (true);   
}

bool set_reflective(char *str, double *to_mod)
{
    if (!str)
        return true;
    if ((!ft_strisfloat(str + 3) && !ft_strisint(str + 3)) || !ft_str_beggin_with(str, "re="))
        return false;
    *to_mod = atof(str + 3);
    if (*to_mod < 0.0 || *to_mod > 1.0)
        return false;
    return true;
}

bool set_specular(char *str, double *to_mod)
{
    if (!str)
        return true;
     if ((!ft_strisfloat(str + 3) && !ft_strisint(str + 3)) || !ft_str_beggin_with(str, "sp="))
        return false;
    *to_mod = atof(str + 3);
    if (*to_mod < 0)
        return false;
    return true;
}

bool set_bonus_options(t_material *mat,char **tab)
{
    int size;
    bool flag = true;
    int i = 0;
    
    size = null_term_tab_len((void **) tab);
    while (i < size)
    {
        if (tab[i] && tab[i][0] != '\n')
            flag = set_reflective(tab[i], &mat->reflective) || set_specular(tab[i], &mat->specular) || set_bump_map_type(mat, tab[i]) || set_checkerboard(mat, tab[i]);
        i++;
    }
    return flag;
}