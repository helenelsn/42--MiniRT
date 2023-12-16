/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_plan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:26:34 by srapin            #+#    #+#             */
/*   Updated: 2023/12/16 20:23:18 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


void set_eq(t_plan *p)
{
    p->a = p->vec.x;
    p->b = p->vec.y;
    p->c = p->vec.z;
    p->d = - p->a * p->p.x - p->b * p->p.y - p->c *p->p.z;
    // printf("a = %f, b= %f, c= %f, d= %f\n", p->a, p->b, p->c, p->d);
}

t_plan *create_plan(char **tab, t_parsing_data *data)
{
    t_plan *elem;

    t_material mat;
    ft_bzero(&mat, sizeof(t_material));
    int size_tab = null_term_tab_len((void **) tab);
    if (size_tab < SP_PL_ARG_SIZE || size_tab > SP_PL_ARG_SIZE + BONUS_SIZE)
        return NULL;
    elem = ft_calloc(1, sizeof(t_plan));
    if (!elem)
        return NULL;
    init_mat(&mat);
    if (!get_rgb(tab[3], &mat.color)|| !get_point(tab[1], &elem->p) || !get_vec_from_str(tab[2], &elem->vec) 
        || !set_bonus_options(&mat, tab + SP_PL_ARG_SIZE))
    {
        free(elem);
        return NULL;
    }
    ft_vlstadd_back(&data->planes, ft_vlstnew_with_mat(elem, free, plan, mat));
    return elem;
}