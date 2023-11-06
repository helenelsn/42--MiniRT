/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:20:17 by srapin            #+#    #+#             */
/*   Updated: 2023/11/05 22:49:43 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_sphere *create_sphere(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_sphere *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_sphere));
    if (!elem)
        return NULL;
    elem->radius = atof(tab[2]) / 2;
    if (!get_rgb(tab[3], &elem->material) || !ft_strisfloat(tab[2]) ||elem->radius < 0 || !get_point(tab[1], &elem->p))
    {
        free(elem);
        return NULL;
    }
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, sphere));
    ft_vlstadd_back(&data->objects, ft_vlstnew(elem, free, sphere));
    t_droite d;
    
    d.p.x = 1;
    d.p.y = 2;
    d.p.z = 0;

    d.v.x = -1;
    d.v.y = 1;
    d.v.z = 1;
      
    //   printf("%f\n", elem->p.z);
    get_inter_for_sphere(elem, d);
    return elem;
}