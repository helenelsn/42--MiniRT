/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:20:17 by srapin            #+#    #+#             */
/*   Updated: 2023/12/15 23:20:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_sphere *create_sphere(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_sphere *elem;
    t_material mat;
    int size_tab;
    ft_bzero(&mat, sizeof(t_material));

    size_tab = null_term_tab_len((void **) tab);
    if ( size_tab != 4 && size_tab != 5
        && size_tab != 6)
        return NULL;
    elem = ft_calloc(1, sizeof(t_sphere));
    if (!elem)
        return NULL;
    elem->radius = atof(tab[2]) / 2;
    if (!get_rgb(tab[3], &mat.color.hex) || !ft_strisfloat(tab[2]) ||elem->radius < 0
        || !get_point(tab[1], &elem->p) || (size_tab > 4 && (!set_specular(tab[4], &mat.specular)))
        || (size_tab > 5 && !set_reflective(tab[5], &mat.reflective)))
        {
            free(elem);
            return NULL;
        }
    if (!mat.specular)
        mat.specular = -1;
        
    mat.textures.bump_mapping = false;
    // if 'do bump mapping'
        // mat.textures.bump_mapping = construct_map(&mat.textures.normap, "./normal_maps/sand");
    
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, sphere));
    ft_vlstadd_back(&data->objects, ft_vlstnew_with_mat(elem, free, sphere, mat));
    return elem;
}