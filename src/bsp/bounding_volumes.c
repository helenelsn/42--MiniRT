/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_volumes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:35:11 by Helene            #+#    #+#             */
/*   Updated: 2023/11/04 13:14:56 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

double  ft_min(double a, double b)
{
    if (a < b)
        return (a);
    return (b);
}

double  ft_max(double a, double b)
{
    if (a > b)
        return (a);
    return (b);
}

t_point_3d double_to_point(double a)
{
    t_point_3d p;
    
    p.x = a;
    p.y = a;
    p.z = a;
    return (p);
}

t_point_3d  points_addition(t_point_3d *p1, t_point_3d *p2)
{
    t_point_3d  new;

    new.x = p1->x + p2->x;
    new.y = p1->y + p2->y;
    new.z = p1->z + p2->z;
    return (new);
}

void    init_bbox(t_bbox_description *bv)
{
    int i;

    i = 0;
    bv->surface_area = 0;
    bv->height = 0;
    bv->length = 0;
    bv->width = 0;
    // while (i < 6)
    // {
    //     bv->coord[i] = 0;
    //     i++;
    // }
}

void    bbox_reset(t_bbox_description *bv, t_point_3d p)
{
    bv->min = p;
    bv->max = p;
    bv->surface_area = 0;
    bv->height = 0;
    bv->length = 0;
    bv->width = 0;
}

void    bbox_add_point(t_bbox_description *bv, t_point_3d p)
{
    bv->min.x = ft_min(bv->min.x, p.x);
    bv->max.x = ft_max(bv->max.x, p.x);
    bv->min.y = ft_min(bv->min.y, p.y);
    bv->max.y = ft_max(bv->max.y, p.y);
    bv->min.z = ft_min(bv->min.z, p.z);
    bv->max.z = ft_max(bv->max.z, p.z);
}

void    set_infos(t_bbox_description *bv)
{
    
}

void    set_sphere_bbox(t_sphere *sphere)
{
    bbox_reset(&sphere->material.bbox, points_addition(sphere->p, double_to_point(-(sphere->radius))));
    bbox_add_point(&sphere->material.bbox, points_addition(sphere->p, double_to_point(sphere->radius)));
}

void    set_cylinder_bbox(t_cylindre *cylinder)
{
    
}

void    set_cone_bbox(t_cone *cone)
{
    
}
/*
For planes, the bounding box will stretch from 
− ∞ to ∞ in at least two axis. 
Keeping these in the hierarchy would 
reduce its effectiveness significantly, and in general our scenes 
tend to contain few planes. 
A scene with a thousand triangles or spheres is interesting, 
a scene with a thousand planes is not.
*/

void    set_bounding_boxes(objects)
{
    t_vlist **current;

    *current = objects;
    while (*current)
    {
        if ((*current)->type == sphere)
            set_sphere_bbox((*current)->content);
        else if ((*current)->type == cylindre)
            set_cylinder_bbox((*current)->content);
        else if ((*current)->type == cone)
            set_cone_bbox((*current)->content);
        *current = (*current)->next;
    }
}
