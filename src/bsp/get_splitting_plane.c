/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splitting_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:51:57 by Helene            #+#    #+#             */
/*   Updated: 2023/11/03 16:03:07 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

double get_voxel_surface_area()
{
    
}

void    bbox_voxel_intersect()
{
    
}

int     items_count_left_side()
{
    
}

/* pondère selon la taille des objets dans le voxel */
double  get_intersection_cost(t_bbox_description bv)
{
    double  sa;

    sa = get_voxel_surface_area(); 
    return (UNITARY_INTERSECT_COST * sa);   
}

double  get_traverse_cost() /* est une constante ou pas ? */
{
    
}

/*  

Nécessite : le voxel parent, et l'intersection plan séparateur - voxel parent
*/
double  compute_cost(t_bsp_node *parent_voxel, double dim, double componant, t_bbox_voxel_intersect_info *info, double sa_voxel)
{
    double  cost;
    double  nb_left;
    double  nb_right;

    nb_left = items_count_left_side();
    nb_right = parent_voxel->items - nb_left;
    cost = TRAVERSE_COST + get_intersection_cost() 
        * (( * nb_left) + ( * nb_right)) / get_voxel_surface_area(parent_voxel);
    /* f(x) = Ct + Ci * (( (SAl(x) * Nl(x)) + (SAr(x) * Nr(x)) ) / SAparent) */
    
    /* Pondère le coût pour privilégier de grands voxels vides */
    if (!nb_left || !nb_right)
        return (0.8 * cost);
    else
        return (cost);
}

t_bbox_voxel_intersect_info get_infos(t_bsp_node *voxel, t_dim split_dim, t_bbox_description bbox)
{
    
}

t_plan set_split_plane()
{
    
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
void    get_splitting_plane(t_bsp_node *current_node)
{
    int     i;
    double  curr_cost;
    double  min_cost;
    t_plan  split_plane;
    t_vlist **curr_obj;
    bool    first;
    double  sa_voxel;
    
    *curr_obj = current_node->items;
    first = true;
    
    while (*curr_obj) /* itère sur chaque objet dans le voxel parent */
    {
        i = 0;
        while (i < 6) /* itère sur les 6 faces de la bounding box de l'objet */
        {
            
            curr_cost = compute_cost(current_node, get_infos(current_node, i % 3, (*curr_obj)->content->material->bbox));
            if (first)
            {
                min_cost = curr_cost;
                split_plane = set_split_plane();
                first = false;
            }
            else if (curr_cost < min_cost)
            {
                min_cost = curr_cost;
                split_plane = set_split_plane();
            }
            i++;
        }
        *curr_obj = (*curr_obj)->next;
    }
    current_node->split_plane = split_plane; /* ? */
}

void    init_bbox(t_bbox_description *bv);

t_bbox_description get_scene_limits(t_vlist *objects)
{
    int     i;
    t_vlist **current;
    t_bbox_description scene_space;

    *current = objects;
    init_bbox(&scene_space);
    i = 0;
    while (i < 6)
    {
        scene_space.coord[i] = ( (2 * (i % 2) - 1) * (-1)) * DBL_MAX; /* floating point numbers are symmetrical */
        i++;
    }
    while (*current)
    {
        i = 0;
        while (i < 6)
        {
            /* ie s'agit d'un min*/
            if (!(i % 2) && (*current)->content->bbox->coord[i] < scene_space.coord[i]) 
                scene_space.coord[i] = (*current)->content->bbox->coord[i];
            else if (i % 2 && (*current)->content->bbox->coord[i] > scene_space.coord[i]) /* ie s'agit d'un max*/
                scene_space.coord[i] = (*current)->content->bbox->coord[i];
            i++;
        }
        *current = (*current)->next;
    }
    /* along x */
    scene_space.length = scene_space.coord[1] = scene_space.coord[0];
    /* along y */
    scene_space.height = scene_space.coord[3] = scene_space.coord[2];
    /* along z */
    scene_space.width = scene_space.coord[5] = scene_space.coord[4];
    scene_space.surface_area = 2 * (scene_space.length * scene_space.height +
        scene_space.height * scene_space.width + scene_space.width * scene_space.length);
    return (scene_space);
}