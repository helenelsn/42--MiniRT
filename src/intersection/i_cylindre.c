/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_cylindre.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:52:41 by srapin            #+#    #+#             */
/*   Updated: 2023/11/06 00:54:00 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_rt.h"


void    get_inter_for_cylindre(t_cylindre *c, t_droite d)
{
    // 
    // t_sphere *s;
    double a;
    double b;
    double c;


    // s = elem->content;

    //trouver les coefficient de l' equation;µ
    //(  ( d.v.x*t) + d.p.x  -  s.p.x)**2 + (  (d.p.y + d.v.y * t) - s.p.y)**2 + (  (d.p.z + d.v.z * t) - s.p.z)**2 -radius **2
   // (x + Y) ** 2 = x**2 +y **2 + 2xy;
   
    a = pow(d.v.x, 2) + pow(d.v.y, 2) + pow(d.v.z, 2); //ok

    
    b = 2 * d.v.x  * (d.p.x - s->p.x) + 2 * d.v.y * (d.p.y - s->p.y) + 2 * d.v.z * (d.p.z - s->p.z );

    c = pow(d.p.x - s->p.x, 2) + pow(d.p.y - s->p.y, 2) + pow(d.p.z - s->p.z, 2) - pow(s->radius, 2);
    

    //get res de leq du second degré
    //reconstruir point sous forme p.x = d.p.x + d.v.x * sol trv au dessus
    
    printf("a = %f, b = %f, c = %f\n", a , b , c);
}