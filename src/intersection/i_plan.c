/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_plan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:10:31 by srapin            #+#    #+#             */
/*   Updated: 2023/12/12 16:13:58 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int    get_inter_for_plan(t_plan *p, t_droite d, t_point *res)
{
    double t;

    normalise(&d.v);
    if (!(p->a * d.v.x +  p->b * d.v.y + p->c * d.v.z))
        return -1;
    // if (p->a * d.p.x + p->b *d.p.y + p->c *d.p.z + p->d) //tocheck droite dans plan?
    //     return -1;
    t = (p->a * d.p.x + p->b * d.p.y + p->c * d.p.z + p->d) / -(p->a * d.v.x +  p->b * d.v.y + p->c * d.v.z);
    res->x =d.p.x + t*d.v.x;
    res->y =d.p.y + t*d.v.y;
    res->z =d.p.z + t*d.v.z;
    return t;

    //get res de leq du second degré
    //reconstruir point sous forme p.x = d.p.x + d.v.x * sol trv au dessus
    
    // printf("a = %f, b = %f, c = %f\n", a , b , c);
}

bool    intersect_plan(t_ray *ray, void *object)
{
    t_plan      *p;
    t_droite    d;
    t_point  res;
    
    
    p = object;
    d.p = ray->origin;
    d.v = ray->direction;
    ray->hit_info.coef = get_inter_for_plan(p, d, &res);
    if (ray->hit_info.coef < 0.0)
    {
        return (false);
    }
        
    
    ray->hit_info.hit_point = res;
    ray->hit_info.distance = get_dist_between_points(ray->origin, ray->hit_info.hit_point);

    
    // printf("---------------------- intersected plan\n");

    return (true);
}
