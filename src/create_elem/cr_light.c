/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:17:10 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 22:38:23 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_light *create_light(char **tab,  t_parsing_data *data)
{
    t_light *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_light));
    if (!elem)
        return NULL;
    elem->infos.ratio = get_ratio(tab[2]);
    if (!get_rgb(tab[3], &elem->infos.color) || elem->infos.ratio < 0 || !get_point(tab[1], &elem->p))
    {
        free(elem);
        return NULL;
    }
    if (data->lights)
        elem->next = data->lights;
    else
        elem->next = NULL;
    elem->infos.emitted_color = color_scale(elem->infos.color, elem->infos.ratio);
    data->lights = elem;
    return elem;
}
