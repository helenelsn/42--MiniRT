/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_cylindre.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:29:43 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 18:04:43 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_cylindre *create_cylindre(char **tab, t_glist **garbage)
{
    t_cylindre *elem;

    if (null_term_tab_len((void **) tab) != 6)
        return NULL;
    elem = ft_calloc(1, sizeof(t_cylindre));
    if (!elem)
        return NULL;
    elem->diam = atof(tab[3]) *(1 - 2 * !ft_strisfloat(tab[3])); //j'trouve c est stylé
    elem->height = atof(tab[4]) *(1 - 2 * !ft_strisfloat(tab[4])); //j'trouve c est stylé

    if (!get_rgb(tab[5], &elem->color) || elem->diam < 0 || elem->height < 0 || !get_point(tab[1], &elem->p) || !get_vec(tab[2], &elem->vec))
    {
        free(elem);
        return NULL;
    }
    ft_glstadd_back(garbage, ft_glstnew(elem, free));
    return elem;
}