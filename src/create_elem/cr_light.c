/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:17:10 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 18:05:42 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_light *create_light(char **tab, t_glist **garbage)
{
    t_light *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_light));
    if (!elem)
        return NULL;
    elem->rat = get_ratio(tab[2]);
    if (!get_rgb(tab[3], &elem->color) || elem->rat < 0 || !get_point(tab[1], &elem->p))
    {
        free(elem);
        return NULL;
    }
    ft_glstadd_back(garbage, ft_glstnew(elem, free));
    return elem;
}