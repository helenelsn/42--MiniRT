/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_plan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:26:34 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 01:27:32 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_plan *create_plan(char **tab, t_glist **garbage)
{
    t_plan *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_plan));
    if (!elem)
        return NULL;
    elem->color = get_rgb(tab[3]);
    if (elem->color < 0 || !get_point(tab[1], &elem->p) || !get_vec(tab[2], &elem->vec))
    {
        free(elem);
        return NULL;
    }
    ft_glstadd_back(garbage, ft_glstnew(elem, free));
    return elem;
}