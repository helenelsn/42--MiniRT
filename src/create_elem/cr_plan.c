/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_plan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:26:34 by srapin            #+#    #+#             */
/*   Updated: 2023/10/19 22:47:56 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_plan *create_plan(char **tab, t_vlist **garbage,t_parsing_data *data)
{
    t_plan *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_plan));
    if (!elem)
        return NULL;
    if (!get_rgb(tab[3], &elem->color)|| !get_point(tab[1], &elem->p) || !get_vec(tab[2], &elem->vec))
    {
        free(elem);
        return NULL;
    }
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, plan));
    ft_vlstadd_back(&data->obj, ft_vlstnew(elem, free, plan));
    return elem;
}