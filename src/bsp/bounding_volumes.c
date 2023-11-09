/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_volumes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:35:11 by Helene            #+#    #+#             */
/*   Updated: 2023/11/08 20:10:00 by hlesny           ###   ########.fr       */
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

double  ft_max_double(double a, double b)
{
    if (a > b)
        return (a);
    return (b);
}

void    set_point(t_point_3d *p, double x, double y, double z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

t_point_3d double_to_point(double a)
{
    t_point_3d p;
    
    p.x = a;
    p.y = a;
    p.z = a;
    return (p);
}

t_point_3d  points_addition(t_point_3d p1, t_point_3d p2)
{
    t_point_3d  new;

    new.x = p1.x + p2.x;
    new.y = p1.y + p2.y;
    new.z = p1.z + p2.z;
    return (new);
}

t_vec_3d vectors_addition(t_vec_3d u, t_vec_3d v)
{
    t_vec_3d w;

    w.x = u.x + v.x;
    w.y = u.y + v.y;
    w.z = u.z + v.z;
    /* set norm ? */
    return (w);
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
    bv->max.x = ft_max_double(bv->max.x, p.x);
    bv->min.y = ft_min(bv->min.y, p.y);
    bv->max.y = ft_max_double(bv->max.y, p.y);
    bv->min.z = ft_min(bv->min.z, p.z);
    bv->max.z = ft_max_double(bv->max.z, p.z);
}

/* to be done at the end : sets the width, height, length and surface_area */
void    set_infos(t_bbox_description *bbox)
{
    /* along x */
    bbox->length = bbox->max.x - bbox->min.x;
    /* along y */
    bbox->height = bbox->max.y - bbox->min.y;
    /* along z */
    bbox->width = bbox->max.z - bbox->min.z;
    bbox->surface_area = 2 * (bbox->length * bbox->height +
        bbox->height * bbox->width + bbox->width * bbox->length);
}

void    set_bbox(t_bbox_description *bv, t_point_3d min, t_point_3d max)
{
    bv->min = min;
    bv->max = max;
    set_infos(bv);
}

void    set_sphere_bbox(t_vlist *object)
{
    t_sphere    *sphere;

    sphere = object->content;
    bbox_reset(&object->material.bbox, points_addition(sphere->p, double_to_point(-(sphere->radius))));
    bbox_add_point(&object->material.bbox, points_addition(sphere->p, double_to_point(sphere->radius)));
}

void    set_cylinder_bbox(t_vlist *object)
{
    t_cylindre *cylinder;

    cylinder = object->content;
    bbox_reset(&object->material.bbox, points_addition(cylinder->p,  double_to_point(cylinder->radius)));
    bbox_add_point(&object->material.bbox, points_addition(cylinder->p,  double_to_point(-(cylinder->radius))));
    bbox_add_point(&object->material.bbox, points_addition(points_addition(cylinder->p,  double_to_point(cylinder->radius)),  double_to_point(cylinder->height)));
}

void    set_cone_bbox(t_vlist *object)
{
    t_cone *cone;

    cone = object->content;
    bbox_reset(&object->material.bbox, points_addition(cone->base.center,  double_to_point(cone->base.radius)));
    bbox_add_point(&object->material.bbox, points_addition(cone->base.center,  double_to_point(-(cone->base.radius))));
    bbox_add_point(&object->material.bbox, points_addition(cone->base.center,  double_to_point(cone->height)));
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

void    set_bounding_boxes(t_vlist *objects)
{
    t_vlist *current;

    current = objects;
    while (current)
    {
        if ((current)->type == sphere)
            set_sphere_bbox(current);
        else if ((current)->type == cylindre)
            set_cylinder_bbox(current);
        else if ((current)->type == cone)
            set_cone_bbox(current);
        /* implémenter pour les autres formes plus tard */
        current = (current)->next;
    }
}

bool    point_is_in(t_bbox_description bv, t_point_3d p)
{
    if (p.x < bv.min.x || p.x > bv.max.x)
        return (false);
    if (p.y < bv.min.y || p.y > bv.max.y)
        return (false);
    if (p.z < bv.min.z || p.z > bv.max.z)
        return (false);
    return (true);
}

/* return if the object should be taken into account in the intersection cost computation,
based on the amount of object's surface area contained in the voxel 
(since an object could be overlaping a voxel) */
bool  count_in_cost(t_bbox_description voxel, t_vlist *object)
{
   t_bbox_description in_v;

    set_bbox(&in_v, object->material.bbox.min, object->material.bbox.max);
    if (object->material.bbox.min.x < voxel.min.x)
        in_v.min.x = voxel.min.x;
    if (object->material.bbox.min.y < voxel.min.y)
        in_v.min.y = voxel.min.y;
    if (object->material.bbox.min.z < voxel.min.z)
        in_v.min.z = voxel.min.z;
    if (object->material.bbox.max.x < voxel.max.x)
        in_v.max.x = voxel.max.x;
    if (object->material.bbox.max.y < voxel.max.y)
        in_v.max.y = voxel.max.y;
    if (object->material.bbox.max.z < voxel.max.z)
        in_v.max.z = voxel.max.z;
    set_infos(&in_v);
    return ((in_v.surface_area / object->material.bbox.surface_area) >= 0.5 );
}

/* 3 cas :
    - est entièrement dans le voxel
        ->  voxel.min[i] <= object.min[i], et voxel.max[i] >= object.max[i]
            -> object.min et object.max sont dans [voxel.min, voxel.max]
        OU  object.min[i] < voxel.min[i] ET object.max[i] > voxel.max[i]
            (l'objet englobe le voxel)
    
    - est entièrement en dehors du voxel
        ->  voxel.min[i] > object.max[i], ou object.min[i] > voxel.max[i]
            -> ni object.min ni object.max ne sont dans [voxel.min, voxel.max]
    
    - coupe le voxel
        ->  object.min[i] < voxel.min[i] et (object.max[i] < object.max[i])
            OU 
            object.min[i] > voxel.min[i] et (object.max[i] > object.max[i])
            -> object.min ou object.max est dans [voxel.min, voxel.max]
        ->  dans ce cas la : si a plus de la moitié dedans, le prend en compte
            dans le calcul du cout d'intersection. sinon, non
*/
bool    is_in_subvoxel(t_bbox_description subvoxel, t_vlist *object)
{
    int     i;
    bool    is_in;

    i = 0;
    is_in = true;
    while (i < 3)
    {
        /* cas ou est entièrement dans le subvoxel */
        if (point_is_in(subvoxel, object->material.bbox.min)
            && point_is_in(subvoxel, object->material.bbox.max))
            return (true);
        /* cas ou est entièrement en dehors le subvoxel */
        if (!point_is_in(subvoxel, object->material.bbox.min)
            && !point_is_in(subvoxel, object->material.bbox.max))
            return (false);
        /* cas ou coupe le subvoxel */
        if ((point_is_in(subvoxel, object->material.bbox.min)
            && !point_is_in(subvoxel, object->material.bbox.max))
            || (!point_is_in(subvoxel, object->material.bbox.min)
            && point_is_in(subvoxel, object->material.bbox.max)))
            return (true);
        i++;
    }
    return (is_in);
}

/* split the objects contained into the parent voxel in the right and left subvoxels*/
void    split_objects(t_bsp_node *parent)
{
    t_vlist *curr_obj;

    curr_obj = parent->items;
    while (curr_obj)
    {
        if (is_in_subvoxel(parent->left->bbox, curr_obj))
        {
            /* add item to the left subvoxel */
            ft_vlstadd_back(&parent->items, curr_obj);
            parent->left->items_count++;
        }
        if (is_in_subvoxel(parent->right->bbox, curr_obj))
        {
            /* add item to the right subvoxel */
            ft_vlstadd_back(&parent->items, curr_obj);
            parent->right->items_count++;
        }
        curr_obj = (curr_obj)->next;
    }
    
    parent->items = NULL; // okou efface tout ?
    parent->items_count = 0;
}

void    split_voxel(t_bsp_node *parent, t_split_infos si)
{
    t_point_3d l_max;
    t_point_3d r_min;
    
    if (si.dim == x)
    {
        set_point(&l_max, si.split_coord, parent->bbox.max.y, parent->bbox.max.z);
        set_point(&r_min, si.split_coord, parent->bbox.min.y, parent->bbox.min.z);
    }
    else if (si.dim == y)
    {
        set_point(&l_max, parent->bbox.max.x, si.split_coord, parent->bbox.max.z);
        set_point(&r_min, parent->bbox.min.x, si.split_coord, parent->bbox.min.z);
    }
    else // if (si.dim == z)
    {
        set_point(&l_max, parent->bbox.max.x, parent->bbox.max.y, si.split_coord);
        set_point(&r_min, parent->bbox.min.x, parent->bbox.min.y, si.split_coord);
    }
    set_bbox(&parent->left->bbox, parent->bbox.min, l_max);
    set_bbox(&parent->right->bbox, r_min, parent->bbox.max);
    parent->left->parent = parent;
    parent->right->parent = parent;
    
    split_objects(parent);
}

t_bbox_description  get_temp_subvoxel(t_bsp_node *parent, t_split_infos si, bool left_subvoxel)
{
    t_point_3d          l_max;
    t_point_3d          r_min;
    t_bbox_description  temp_bbox;
    
    if (si.dim == x)
    {
        if (left_subvoxel)
            set_point(&l_max, si.split_coord, parent->bbox.max.y, parent->bbox.max.z);
        else
            set_point(&r_min, si.split_coord, parent->bbox.min.y, parent->bbox.min.z);
    }
    else if (si.dim == y)
    {
        if (left_subvoxel)
            set_point(&l_max, parent->bbox.max.x, si.split_coord, parent->bbox.max.z);
        else
            set_point(&r_min, parent->bbox.min.x, si.split_coord, parent->bbox.min.z);
    }
    else if (si.dim == z)
    {
        if (left_subvoxel)
            set_point(&l_max, parent->bbox.max.x, parent->bbox.max.y, si.split_coord);
        else
            set_point(&r_min, parent->bbox.min.x, parent->bbox.min.y, si.split_coord);
    }
    if (left_subvoxel)
        set_bbox(&temp_bbox, parent->bbox.min, l_max);
    else
        set_bbox(&temp_bbox, r_min, parent->bbox.max);
    return (temp_bbox);
}
