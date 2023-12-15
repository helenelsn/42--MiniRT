/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:59:16 by srapin            #+#    #+#             */
/*   Updated: 2023/12/15 23:20:19 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_cone *create_cone(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_cone *elem;

    t_material mat;
    ft_bzero(&mat, sizeof(t_material));
    elem = ft_calloc(1, sizeof(t_cone));
    int size_tab = null_term_tab_len((void **) tab);
    if (size_tab < 6 || size_tab > 8)
        return NULL;
    if (!elem)
        return NULL;
    elem->radius = atof(tab[3]) *(1 - 2 * !ft_strisfloat(tab[3])) / 2; //j'trouve c est stylé
    elem->height = atof(tab[4]) *(1 - 2 * !ft_strisfloat(tab[4])); //j'trouve c est stylé
    if (!get_rgb(tab[5], &mat.color) || elem->radius < 0 || elem->height < 0 || !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->vec) || !set_specular(tab[6], &mat.specular) || (size_tab > 7 && !set_reflective(tab[7], &mat.reflective)))
    {
        free(elem);
        return NULL;
    }
    normalise(&elem->vec);
    if (elem->vec.x)
        elem->n0 = cross_product(elem->vec, (t_vec) {0,1,0,1});
    else
        elem->n0 = cross_product(elem->vec, (t_vec) {1,0,0,1});
    elem->n1 = cross_product(elem->vec, elem->n0);
    normalise(&elem->n0);
    normalise(&elem->n1);
    elem->base_to_cyl = new_3x3_matrix_from_vec(elem->n0, elem->vec, elem->n1, false);
    elem->p_to_origin = get_directional_vect(elem->p, (t_point) {0,0,0});
    
    elem->cyl_to_base = get_inverse(elem->base_to_cyl);
    
    elem->origin_to_p = get_directional_vect((t_point) {0,0,0}, elem->p);
    
    t_ray tmp;
    tmp.origin = elem->p;
    tmp.direction = elem->vec;
    
    elem->top = get_ray_point(tmp, elem->height);
    elem->cover_plane = (t_plan) {elem->p, elem->vec, 0,0,0,0};
    set_eq(&elem->cover_plane);
    elem->slant_height = sqrt(pow(elem->radius, 2)+ pow(elem->height, 2));
    // elem->base.center = elem->p;
    
    if (!mat.specular)
        mat.specular = -1;

    mat.textures.bump_mapping = false;
    // if 'do bump mapping'
        // mat.textures.bump_mapping = construct_map(&mat.textures.normap, "./normal_maps/terrain");
        
    // construct_map(&mat.textures.normap, "./normal_maps/terrain");
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, cone));
    ft_vlstadd_back(&data->objects, ft_vlstnew_with_mat(elem, free, cone, mat));
    return elem;
}