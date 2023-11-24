/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:17:10 by srapin            #+#    #+#             */
/*   Updated: 2023/11/24 15:06:06 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_light *create_light(char **tab, t_vlist **garbage, t_parsing_data *data)
{
    t_light *elem;

    if (null_term_tab_len((void **) tab) != 4 || data->lights)
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
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, light));
    data->lights = elem;
    data->lights->next = NULL; //todel, juste la pr eviter les segfaults pdt les tests
    return elem;
}