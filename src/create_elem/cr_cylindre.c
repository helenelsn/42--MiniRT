/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_cylindre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:29:43 by srapin            #+#    #+#             */
/*   Updated: 2023/12/01 15:15:45 by srapin           ###   ########.fr       */
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
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, cylindre));
    ft_vlstadd_back(&data->objects, ft_vlstnew(elem, free, cylindre));
    return elem;
}