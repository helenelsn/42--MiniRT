/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_plan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:26:34 by srapin            #+#    #+#             */
/*   Updated: 2023/11/13 08:21:13 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


void set_eq(t_plan *p)
{
    p->a = p->vec.x;
    p->b = p->vec.y;
    p->c = p->vec.z;
    p->d = - p->a * p->p.x - p->b * p->p.y - p->c *p->p.y;
    // printf("a = %f, b= %f, c= %f, d= %f\n", p->a, p->b, p->c, p->d);
}

t_plan *create_plan(char **tab, t_vlist **garbage,t_parsing_data *data)
{
    t_plan *elem;

    if (null_term_tab_len((void **) tab) != 4)
        return NULL;
    elem = ft_calloc(1, sizeof(t_plan));
    if (!elem)
        return NULL;
    // printf("lool");
    if (!get_rgb(tab[3], &elem->color)|| !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->vec))
    {
        free(elem);
        return NULL;
    }
    // printf("lool");
    set_eq(elem);
    ft_vlstadd_back(garbage, ft_vlstnew(elem, free, plan));
    ft_vlstadd_back(&data->planes, ft_vlstnew(elem, free, plan));
    // t_droite d;
    
    // d.p.x = 1;
    // d.p.y = 2;
    // d.p.z = -3;

    // d.v.x = -2;
    // d.v.y = 0;
    // d.v.z = 3;
    // get_inter_for_plan(elem, d);
    return elem;
}