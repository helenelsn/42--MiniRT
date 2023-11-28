/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_plan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:10:31 by srapin            #+#    #+#             */
/*   Updated: 2023/11/28 02:46:01 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool    get_inter_for_plan(t_plan *p, t_droite d, t_point_3d *res)
{
    double t;

    if (!(p->a * d.v.x +  p->b * d.v.y + p->c * d.v.z))
        return false;
    if (p->a * d.p.x + p->b *d.p.y + p->c *d.p.z + p->d) //tocheck droite dans plan?
        return false;
    t = (p->a * d.p.x + p->b * d.p.y + p->c * d.p.z + p->d) / -(p->a * d.v.x +  p->b * d.v.y + p->c * d.v.z);
    res->x =d.p.x + t*d.v.x;
    res->y =d.p.y + t*d.v.y;
    res->z =d.p.z + t*d.v.z;
    return true;

    //get res de leq du second degré
    //reconstruir point sous forme p.x = d.p.x + d.v.x * sol trv au dessus
    
    // printf("a = %f, b = %f, c = %f\n", a , b , c);
}