/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_mood_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:34:39 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 18:06:15 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_mood_light *create_mood_light(char **tab, t_glist **garbage)
{
    t_mood_light *elem;

    if (null_term_tab_len((void **) tab) != 3)
        return NULL;
    elem = ft_calloc(1, sizeof(t_mood_light));
    if (!elem)
        return NULL;
    elem->rat = get_ratio(tab[1]);
    if (elem->rat < 0 || !get_rgb(tab[2], &elem->color))
    {
        //todo
        free(elem);
        return NULL;
    }
    ft_glstadd_back(garbage, ft_glstnew(elem, free));
    return elem;
}