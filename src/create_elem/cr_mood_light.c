/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_mood_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:34:39 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 20:22:18 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_mood_light *create_mood_light(char **tab,  t_parsing_data *data)
{
    t_mood_light *elem;

    if (null_term_tab_len((void **) tab) != 3 || data->mooooo)
        return NULL;
    elem = ft_calloc(1, sizeof(t_mood_light));
    if (!elem)
        return NULL;
    elem->infos.ratio = get_ratio(tab[1]);
    if (elem->infos.ratio < 0 || !get_rgb(tab[2], &elem->infos.color))
    {
        //todo what?
        free(elem);
        return NULL;
    }
   // ft_vlstadd_back( ft_vlstnew(elem, free, mood_light));
    elem->infos.emitted_color = color_scale(elem->infos.color, elem->infos.ratio);
    data->mooooo = elem;
    return elem;
}