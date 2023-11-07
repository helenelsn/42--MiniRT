/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splitting_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:51:57 by Helene            #+#    #+#             */
/*   Updated: 2023/11/08 00:03:31 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"


int     items_count_subvoxel(t_bsp_node *voxel, t_bbox_description subvoxel)
{
    int     count;
    t_vlist *current;

    count = 0;
    current = voxel->items;
    while(current)
    {
        if (is_in_subvoxel(subvoxel, current))
            count++;
        current = current->next;
    }
}

double  get_object_intersect_cost(t_vlist *object)
{
    /* check if is at least half-entirely on the voxel.
        if not, does not consider it in the cost computation */
    return (UNITARY_INTERSECT_COST * object->material.bbox.surface_area);
}

double get_object_list_intersection_cost(t_bsp_node *voxel)
{
    t_vlist *current;
    double cost;
    
    cost = 0;
    current = voxel->items;
    while (current)
    {
        cost += get_object_intersect_cost(current);
        current = (current)->next;
    }    
    return (cost);
}

/* pondère selon la taille des objets dans le voxel */
double  get_intersection_cost(t_bsp_node *parent, t_split_infos si, bool left_subvoxel)
{
    double              cost;
    t_vlist             *current;
    t_bbox_description  subvoxel;
    
    cost = 0;
    current = parent->items;
    subvoxel = get_temp_subvoxel(parent, si, left_subvoxel);
    while (current)
    {
        if (is_in_subvoxel(subvoxel, current) && count_in_cost(subvoxel, current))
            cost += get_object_intersect_cost(current);
        current = (current)->next;
    }
    return (cost);
}

/*  
Nécessite : le voxel parent, et l'intersection plan séparateur - voxel parent
*/
double  compute_cost(t_bsp_node *voxel, t_split_infos si)
{
    double  cost;
    int     nb_left;
    int     nb_right;
    t_bbox_description  subv_l;
    t_bbox_description  subv_r;

    subv_l = get_temp_subvoxel(voxel, si, true);
    subv_r = get_temp_subvoxel(voxel, si, false);
    nb_left = items_count_subvoxel(voxel, subv_l);
    nb_right = items_count_subvoxel(voxel, subv_r);
    
    cost = TRAVERSE_COST + 
        (get_intersection_cost(voxel, si, true) * (subv_l.surface_area * nb_left) + 
        get_intersection_cost(voxel, si, false) * (subv_r.surface_area * nb_right)) 
        / voxel->bbox.surface_area;
    /* f(x) = Ct + Ci * (( (SAl(x) * Nl(x)) + (SAr(x) * Nr(x)) ) / SAparent) */
    
    /* Pondère le coût pour privilégier de grands voxels vides */
    if (!nb_left || !nb_right)
        return (0.8 * cost);
    else
        return (cost);
}

double  get_i_coordinate(t_point_3d p, int i)
{
    if (i < 0 || i > 2)
        return (-1);
    if (i == 0)
        return (p.x);
    else if (i == 1)
        return (p.y);
    else 
        return (p.z);
}

/* compute the traversing cost for the splitting planes generated 
by the 6 faces of the object's bounding box */
t_split_infos test_bounding_planes(t_bsp_node *parent, t_vlist *object)
{
    int             i;
    t_split_infos   si;
    t_split_infos   final_si;

    i = 0;
    si.dim = x;
    si.split_coord = object->material.bbox.min.x;
    final_si.cost = compute_cost(parent, si);
    while (i < 3)
    {
        si.dim = i;
        
        si.split_coord = get_i_coordinate(object->material.bbox.min, i);
        si.cost = compute_cost(parent, si);
        if (si.cost < final_si.cost)
            final_si = si;
        si.split_coord = get_i_coordinate(object->material.bbox.max, i);
        si.cost = compute_cost(parent, si);
        if (si.cost < final_si.cost)
            final_si = si;
        i++;
    }
    return (final_si);
}

/* 

Find the right splitting plane :
1)  for each object in the items_list of the parent voxel,
    compute the cost.
    -> 2)   Also, for each of the 6 planes of the bounding volume of each object,
            compute the cost.
        ->  regarde a quelle dimension appartient le plan
            ex : si x, alors est la seule composante qui va changer par rapport
            a celles du voxel parent
 */

/* Find the optimal under-voxels of the current voxel, cost-wise 
    -> SAH 
    Pour chaque objet, on teste les 6 plans générés par chaque face 
    du rectangle enveloppant l'objet */
t_split_infos    get_optimal_split_plane(t_bsp_node *current_node)
{
    t_vlist         *curr_obj;
    t_split_infos   si;
    t_split_infos   final_si;
    
    curr_obj = current_node->items;
    final_si = test_bounding_planes(current_node, curr_obj);
    /* itère sur chaque objet dans le voxel parent */
    while (curr_obj)
    {
        /* par objet : retourne le plan le plus optimal parmi les 6 plans générés par la bbox */
        si = test_bounding_planes(current_node, curr_obj);
        if (si.cost < final_si.cost)
            final_si = si;
        curr_obj = (curr_obj)->next;
    }
    // split_voxel(current_node, final_si);
    return (final_si);
}

/* set the englobing boundig box */
t_bbox_description get_scene_limits(t_vlist *objects)
{
    t_vlist *current;
    t_bbox_description scene_space;

    current = objects;
    bbox_reset(&scene_space, current->material.bbox.min);
    while (current)
    {
        bbox_add_point(&scene_space, current->material.bbox.min);
        bbox_add_point(&scene_space, current->material.bbox.max);
        current = current->next;
    }
    set_infos(&scene_space);
    return (scene_space);
}