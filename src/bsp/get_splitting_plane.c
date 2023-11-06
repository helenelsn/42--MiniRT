/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splitting_plane.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:51:57 by Helene            #+#    #+#             */
/*   Updated: 2023/11/06 12:22:32 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"


void    bbox_voxel_intersect()
{
    
}

int     items_count_left_side()
{
    
}

bool    is_in_subvoxel(t_bbox_description voxel, t_vlist *object, t_split_infos si)
{
    if (object->content->material.bbox.min)
}

double  get_object_intersect_cost(t_vlist *object)
{
    return (UNITARY_INTERSECT_COST * object->content->material.bbox.surface_area);
}

/* pondère selon la taille des objets dans le voxel */
double  get_intersection_cost(t_bsp_node *parent)
{
    t_vlist **current;
    double cost;
    
    cost = 0;
    *current = parent->items;
    while (*current)
    {
        cost += get_object_intersect_cost()
        *current = (*current)->next;
    }
      
}

double  get_traverse_cost() /* est une constante ou pas ? */
{
    
}

/*  

Nécessite : le voxel parent, et l'intersection plan séparateur - voxel parent
*/
double  compute_cost(t_bsp_node *parent_voxel, double dim, double componant)
{
    double  cost;
    double  nb_left;
    double  nb_right;
    double  sa_left;
    double  sa_right;

    nb_left = items_count_left_side();
    nb_right = parent_voxel->items - nb_left;
    sa_left = ;
    sa_right = parent_voxel->bbox.surface_area - sa_left;
    cost = TRAVERSE_COST + 
        (get_intersection_cost() * (sa_left * nb_left) + 
        get_intersection_cost() * (sa_right * nb_right)) / get_voxel_surface_area(parent_voxel);
    /* f(x) = Ct + Ci * (( (SAl(x) * Nl(x)) + (SAr(x) * Nr(x)) ) / SAparent) */
    
    /* Pondère le coût pour privilégier de grands voxels vides */
    if (!nb_left || !nb_right)
        return (0.8 * cost);
    else
        return (cost);
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
    t_vlist **curr_obj;
    bool    first;
    
    
    *curr_obj = current_node->items;
    first = true;
    
    while (*curr_obj) /* itère sur chaque objet dans le voxel parent */
    {
        
        *curr_obj = (*curr_obj)->next;
    }
}

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
    scene_space.length = scene_space.coord[1] - scene_space.coord[0];
    /* along y */
    scene_space.height = scene_space.coord[3] - scene_space.coord[2];
    /* along z */
    scene_space.width = scene_space.coord[5] - scene_space.coord[4];
    scene_space.surface_area = 2 * (scene_space.length * scene_space.height +
        scene_space.height * scene_space.width + scene_space.width * scene_space.length);
    return (scene_space);
}