/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:20:17 by srapin            #+#    #+#             */
/*   Updated: 2023/12/13 17:22:00 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_sphere *create_sphere(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_sphere *elem;
    t_raytracing_material mat;
    ft_bzero(&mat, sizeof(t_raytracing_material));

    if (null_term_tab_len((void **) tab) != 4 && null_term_tab_len((void **) tab) != 5
        && null_term_tab_len((void **) tab) != 6)
        return NULL;
    elem = ft_calloc(1, sizeof(t_sphere));
    if (!elem)
        return NULL;
    elem->radius = atof(tab[2]) / 2;
    if (!get_rgb(tab[3], &mat.color.hex) || !ft_strisfloat(tab[2]) ||elem->radius < 0
        || !get_point(tab[1], &elem->p) || !set_specular(tab[4], &mat.specular)
        || (tab[5] && !set_reflective(tab[5], &mat.reflective)))
        {
            free(elem);
            return NULL;
        }
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, sphere));
    ft_vlstadd_back(&data->objects, ft_vlstnew_with_mat(elem, free, sphere, mat));
    // printf("------------------------------------ rgb_to_hex = %u    %f %f %f\n", mat.color, elem->p.x, elem->p.y, elem->p.z);
    // t_droite d;
    
    // d.p.x = 1;
    // d.p.y = 2;
    // d.p.z = 0;

    // d.v.x = -1;
    // d.v.y = 1;
    // d.v.z = 1;
      
    //   printf("%f\n", elem->p.z);
    // get_inter_for_sphere(elem, d);
    return elem;
}