/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_mood_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:34:39 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 22:48:43 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_mood_light *create_mood_light(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_mood_light *elem;

    if (null_term_tab_len((void **) tab) != 3 || data->moo)
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
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, mood_light));
    data->moo = elem;
    return elem;
}