/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:20:17 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 01:24:34 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_sphere *create_sphere(char **tab, t_glist **garbage)
{
    t_sphere *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_sphere));
    if (!elem)
        return NULL;
    elem->diam = atof(tab[2]);
    elem->color = get_rgb(tab[3]);
    if (elem->color < 0 || !ft_strisfloat(tab[2]) ||elem->diam < 0 || !get_point(tab[1], &elem->p))
    {
        free(elem);
        return NULL;
    }
    ft_glstadd_back(garbage, ft_glstnew(elem, free));
    return elem;
}