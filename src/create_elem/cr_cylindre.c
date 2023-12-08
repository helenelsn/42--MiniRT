/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_cylindre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:29:43 by srapin            #+#    #+#             */
/*   Updated: 2023/12/07 00:27:01 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


t_cylindre *create_cylindre(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_cylindre *elem;

    if (null_term_tab_len((void **) tab) != 7 && null_term_tab_len((void **) tab) != 6)
        return NULL;
    elem = ft_calloc(1, sizeof(t_cylindre));
    if (!elem)
        return NULL;
    elem->radius = atof(tab[3]) *(1 - 2 * !ft_strisfloat(tab[3])) / 2; //j'trouve c est stylé
    elem->height = atof(tab[4]) *(1 - 2 * !ft_strisfloat(tab[4])); //j'trouve c est stylé
    if (!get_rgb(tab[5], &elem->color) || elem->radius < 0 || elem->height < 0 || !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->vec) || !set_specular(tab[6], &elem->specular))
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
    
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, cylindre));
    ft_vlstadd_back(&data->objects, ft_vlstnew(elem, free, cylindre));
    return elem;
}