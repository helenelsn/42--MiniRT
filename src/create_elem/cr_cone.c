/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:59:16 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 21:06:34 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


void set_cone_dep(t_cone *elem)
{
    t_ray tmp;
    tmp.origin = elem->p;
    tmp.direction = elem->vec;
    
    elem->top = get_ray_point(tmp, elem->height);
    elem->cover_plane = (t_plan) {elem->p, elem->vec, 0,0,0,0};
    set_eq(&elem->cover_plane);
}

// bool set_checkerboard(t_material *mat,char *info)
// {
//     if (!info || info[0] != 'c')
//         return false;
//     mat->textures.checkered = true;
//     return (true);   
// }

// bool set_bump_map_type(t_material *mat,char *info)
// {
//     if (!info || info[0] != 'b')
//         return false;
//     if (!info[1])
//         mat->textures.t = 0;
//     else if (info[2] == 'c')
//         mat->textures.t = cliff;
//     else if(info[2] == 's')
//         mat->textures.t = sand;
//     else if (info[2] == 't' && info[2] == 'e')
//         mat->textures.t = terrain;
//     else if (info[2] == 't' && info[2] == 'r')
//         mat->textures.t = tree;
//     else if (info[2] == 'w')
//         mat->textures.t = wood;
//     else
//         return (false);
//     mat->textures.bump_mapping = true;
//     return (true);   
// // }

// void init_mat(t_material *mat)
// {
//     mat->specular = -1;
//     mat->textures.checkered = false;
//     mat->textures.bump_mapping = false;
//     mat->textures.t = no_map;
//     mat->reflective = 0;
// }

t_cone *create_cone(char **tab,  t_parsing_data *data)
{
    t_material mat;
    t_cone *elem;
    bool flag;
    int size_tab = null_term_tab_len((void **) tab);

    if (size_tab < CO_CY_ARG_SIZE || size_tab > CO_CY_ARG_SIZE + BONUS_SIZE)
        return NULL;
    elem = ft_calloc(1, sizeof(t_cone));
    if (!elem)
        return NULL;
    init_mat(&mat);
    elem->radius = atof(tab[3]) *(1 - 2 * !ft_strisfloat(tab[3])) / 2; //j'trouve c est stylé
    elem->height = atof(tab[4]) *(1 - 2 * !ft_strisfloat(tab[4])); //j'trouve c est stylé
    if (!get_rgb(tab[5], &mat.color) || elem->radius < 0 || elem->height < 0 || !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->vec) || !set_bonus_options(&mat, tab + CO_CY_ARG_SIZE))
    {
        free(elem);
        return NULL;
    }
    normalise(&elem->vec);
    set_cone_dep(elem);
    ft_vlstadd_back(&data->objects, ft_vlstnew_with_mat(elem, free, cone, mat));
    return elem;
}