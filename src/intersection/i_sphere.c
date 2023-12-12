/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:19:12 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 21:06:42 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool    intersect_sphere(t_ray *ray, void *object)
{
    t_sphere    *sp;
    t_quadratic eq;
    t_vec       center_to_origin;
    double      mult;

    sp = object;
    center_to_origin = get_directional_vect(sp->p, ray->origin);
    eq.a = dot(ray->direction, ray->direction);
    eq.b = 2 * dot(center_to_origin, ray->direction);
    eq.c = dot(center_to_origin, center_to_origin) - sp->radius * sp->radius;
    if (!solve_quadratic_eq(&eq))
        return (false);
    mult = get_closest_point(eq.t_1, eq.t_2);
    ray->hit_info.hit_point.x = ray->origin.x + ray->direction.x * mult;
    ray->hit_info.hit_point.y = ray->origin.y + ray->direction.y * mult;
    ray->hit_info.hit_point.z = ray->origin.z + ray->direction.z * mult;
    ray->hit_info.coef = mult;
    // printf("%f", mult);
    ray->hit_info.distance = get_dist_between_points(ray->origin, ray->hit_info.hit_point);
    
    if (ray->hit_info.coef <= 0.001)
        ray->hit_info.distance = -1;
    // ray->hit_info.distance = mult;

    //printf("------------- {%s}, ray{O(%f, %f, %f), D(%f, %f, %f)} intersected sphere{C(%f, %f, %f)}\n",
    //    __func__, ray->origin.x, ray->origin,y, ray->origin.z, ray->direction.x, ray->direction.y, ray->direction.z, sp->p.x, sp->p.y, sp->p.z);
    
    return (ray->hit_info.distance != -1);
}


// ok de commenter la fonction en dessous ?

// void    get_inter_for_sphere(t_sphere *s, t_droite d)
// {
//     // 
//     // t_sphere *s;
//     double a;
//     double b;
//     double c;


//     // s = elem->content;

//     //trouver les coefficient de l' equation;µ
//     //(  ( d.v.x*t) + d.p.x  -  s.p.x)**2 + (  (d.p.y + d.v.y * t) - s.p.y)**2 + (  (d.p.z + d.v.z * t) - s.p.z)**2 -radius **2
//    // (x + Y) ** 2 = x**2 +y **2 + 2xy;
   
//     a = pow(d.v.x, 2) + pow(d.v.y, 2) + pow(d.v.z, 2); //ok

    
//     b = 2 * d.v.x  * (d.p.x - s->p.x) + 2 * d.v.y * (d.p.y - s->p.y) + 2 * d.v.z * (d.p.z - s->p.z );

//     c = pow(d.p.x - s->p.x, 2) + pow(d.p.y - s->p.y, 2) + pow(d.p.z - s->p.z, 2) - pow(s->radius, 2);
    

//     //get res de leq du second degré
//     //reconstruir point sous forme p.x = d.p.x + d.v.x * sol trv au dessus
    
//     printf("a = %f, b = %f, c = %f\n", a , b , c);
// }