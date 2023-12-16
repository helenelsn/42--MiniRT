/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_volumes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:35:11 by Helene            #+#    #+#             */
/*   Updated: 2023/12/16 01:26:32 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"


double  ft_max_double(double a, double b)
{
    if (a > b)
        return (a);
    return (b);
}

void    bbox_reset(t_bbox_description *bv, t_point p)
{
    bv->min = p;
    bv->max = p;
    bv->surface_area = 0;
    bv->height = 0;
    bv->length = 0;
    bv->width = 0;
}

void    bbox_add_point(t_bbox_description *bv, t_point p)
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

void    set_bbox(t_bbox_description *bv, t_point min, t_point max)
{
    bv->min = min;
    bv->max = max;
    set_infos(bv);
}

void    set_sphere_bbox(t_vlist *object)
{
    t_sphere    *sphere;

    sphere = object->content;
    bbox_reset(&object->material.bbox, point_addition(sphere->p, double_to_point(-(sphere->radius + T_INF))));
    bbox_add_point(&object->material.bbox, point_addition(sphere->p, double_to_point(sphere->radius + T_INF)));
}


void    set_cylinder_bbox(t_vlist *object)
{
    t_cylindre *cylinder;

    cylinder = object->content;
    bbox_reset(&object->material.bbox, point_addition(cylinder->p,  double_to_point(cylinder->radius + T_INF)));
    bbox_add_point(&object->material.bbox, point_addition(cylinder->p,  double_to_point(-(cylinder->radius + T_INF))));
    bbox_add_point(&object->material.bbox, point_addition(point_addition(cylinder->p,  double_to_point(cylinder->radius + T_INF)),
        double_to_point(cylinder->height + T_INF)));
}

void    set_cone_bbox(t_vlist *object)
{
    t_cone *cone;

    cone = object->content;
    bbox_reset(&object->material.bbox, point_addition(cone->p,  double_to_point(cone->radius + T_INF)));
    bbox_add_point(&object->material.bbox, point_addition(cone->p,  double_to_point(-(cone->radius + T_INF))));
    bbox_add_point(&object->material.bbox, point_addition(cone->p,  double_to_point(cone->height + T_INF)));
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
        set_infos(&current->material.bbox);
        current = (current)->next;
    }
}

bool    point_is_in(t_bbox_description bv, t_point p)
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
double  count_in_cost(t_bbox_description voxel, t_vlist *object)
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
    if (object->material.bbox.surface_area == 0)
        return (0);
    return ((in_v.surface_area / object->material.bbox.surface_area));
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

t_vlist *ft_vlstnew_with_mat(void * content, void foo(void *), t_type t,
    t_material mat)
{
    t_vlist *new;

    new = ft_vlstnew(content, foo, t);
    new->material = mat;

    //todel
    new->material.textures.checkered = false;
    // new->material.textures.bump_mapping = true; //ln
    
    set_checkerboard_map(&new->material.textures.checkerboard, new->type, (t_color){0xffffff});
    
    // set_color_in_mat(content, &mat, t);
    // printf("%d", mat.color);
    return (new);
}

/* split the objects contained into the parent voxel in the right and left subvoxels*/
void    split_objects(t_bsp_node *parent)
{
    t_vlist *curr_obj;

    curr_obj = parent->items;
    while (curr_obj)
    {
        if (parent->left && is_in_subvoxel(parent->left->bbox, curr_obj))
        {
            /* add item to the left subvoxel */

            // !!!!!!!!!!!! il faut malloc
            ft_vlstadd_back(&parent->left->items, ft_vlstnew_with_mat(curr_obj->content,
                curr_obj->free_foo, curr_obj->type, curr_obj->material));
            parent->left->items_count++;
        }
        if (parent->right && is_in_subvoxel(parent->right->bbox, curr_obj))
        {
            /* add item to the right subvoxel */

             // !!!!!!!!!!!! il faut malloc
            ft_vlstadd_back(&parent->right->items, ft_vlstnew_with_mat(curr_obj->content,
                curr_obj->free_foo, curr_obj->type, curr_obj->material));
            parent->right->items_count++;
        }
        curr_obj = (curr_obj)->next;
    }
    if (parent->left)
        parent->left->depth = parent->depth + 1;
    if (parent->right)
        parent->right->depth = parent->depth + 1;

    parent->items = NULL; // ok ou efface tout ?
    parent->items_count = 0;
}

void    set_subvoxels(t_bsp_node *parent, t_point l_max, t_point r_min)
{
    parent->left = NULL;
    parent->right = NULL;
    if (parent->bbox.min.x < l_max.x && parent->bbox.min.y < l_max.y
        && parent->bbox.min.z < l_max.z) // ou !=
        {
            parent->left = ft_calloc(sizeof(t_bsp_node), 1);
            if (!parent->left)
                return ; // idk
            set_bbox(&parent->left->bbox, parent->bbox.min, l_max);
            parent->left->parent = parent;
        }
    if (parent->bbox.max.x > r_min.x && parent->bbox.max.y > r_min.y
        && parent->bbox.max.z > r_min.z) // ou !=
        {
            parent->right = ft_calloc(sizeof(t_bsp_node), 1);
            if (!parent->right)
                return ; // idk
            set_bbox(&parent->right->bbox, r_min, parent->bbox.max);
            parent->right->parent = parent;
        }
   
    /* parent->right = ft_calloc(sizeof(t_bsp_node), 1);
    if (!parent->right)
        return ; // idk
    
    // mieux formuler
    if (parent->bbox.min.x == l_max.x)
        free(parent->left);
    // pareil pour y et z, et pour parent->bbox.max et r_min 
    
    
    set_bbox(&parent->right->bbox, r_min, parent->bbox.max);
    
    parent->right->parent = parent; */
    
    split_objects(parent);
}

void    split_voxel(t_bsp_node *parent, t_split_infos si)
{
    t_point l_max;
    t_point r_min;
    
    parent->split_inf = si;
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
    
    set_subvoxels(parent, l_max, r_min);
}

t_bbox_description  get_temp_subvoxel(t_bsp_node *parent, t_split_infos si, bool left_subvoxel)
{
    t_point          l_max;
    t_point          r_min;
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
