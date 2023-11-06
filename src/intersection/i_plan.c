/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_plan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:10:31 by srapin            #+#    #+#             */
/*   Updated: 2023/11/06 00:44:18 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void    get_inter_for_plan(t_plan *p, t_droite d)
{
    // 
    // t_sphere *s;
    // double a;
    // double b;
    double t;



    // s = elem->content;

    //trouver les coefficient de l' equation;µ
    // res eq plan = ax + by + cz +d

    // 0 = p->a * (d.p.x + d.v.x * t) + p->b * (d.p.y + d.v.y * t) + p->c * (d.p.z + d.v.z * t) + p->d;
    // 0 = p->a * d.p.x +  p->a * d.v.x * t + p->b * d.p.y +  p->b * d.v.y * t + p->c * d.p.z +   p->c * d.v.z * t + p->d;
    // t * -(p->a * d.v.x +  p->b * d.v.y + p->c * d.v.z) = p->a * d.p.x + p->b * d.p.y + p->c * d.p.z + p->d;

    if (!(p->a * d.v.x +  p->b * d.v.y + p->c * d.v.z))
        return;
    t = (p->a * d.p.x + p->b * d.p.y + p->c * d.p.z + p->d) / -(p->a * d.v.x +  p->b * d.v.y + p->c * d.v.z);
    printf( "%f \n", t);
    //todo recreate point et ret

    //get res de leq du second degré
    //reconstruir point sous forme p.x = d.p.x + d.v.x * sol trv au dessus
    
    // printf("a = %f, b = %f, c = %f\n", a , b , c);
}