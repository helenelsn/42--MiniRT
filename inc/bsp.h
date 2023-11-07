/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:46:51 by Helene            #+#    #+#             */
/*   Updated: 2023/11/06 18:32:59 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_H
# define BSP_H

#include <stdbool.h>
#include "struct.h"

/* variables pour les conditions d'arrêt de la fonction récursive créant l'arbre */
# define    MAX_DEPTH   5 /* profondeur maximale de l'arbre */

# define TRAVERSE_COST          1 // a modif /* cost of traversing an inner node */ 
# define UNITARY_INTERSECT_COST 1 // a modif /* cost of intersecting a triangle (ici ne décompose pas en triangles, donc devra ponderer selon la surface de l'objet i guess) */

/* 
In ray tracing the internal nodes of a space subdivision are not interesting.
All useful information is in the leaves.
*/

typedef enum    e_node_type
{
    node,
    leaf  
}               t_node_type;

typedef enum    e_dim
{
    x,
    y,
    z
}               t_dim;

typedef struct  s_split_infos
{
    t_dim   dim;
    double  split_coord;
    double  cost;
}               t_split_infos;

typedef struct s_bsp_node
{
    t_node_type         type; 
    int                 depth; /* ? */
    
    t_bbox_description  bbox;
    
    t_vlist             *items; /* NULL when not a leaf */
    int                 items_count; /* 0 when not a leaf ? */
    
    struct s_bsp_node    *left;
    struct s_bsp_node    *right;
}               t_bsp_node;


double              compute_cost(t_bsp_node *parent_voxel, t_split_infos si);
t_split_infos       get_splitting_plane(t_bsp_node *current_node);
t_bbox_description  get_scene_limits(t_vlist *objects);
void                set_bounding_boxes(t_vlist *objects);
void                init_bbox(t_bbox_description *bv);
void                split_voxel(t_bsp_node *parent, t_split_infos si);
t_bbox_description  get_temp_subvoxel(t_bsp_node *parent, t_split_infos si, bool left_subvoxel);
bool                is_in_subvoxel(t_bbox_description *subvoxel, t_vlist *object);
double              get_intersection_cost(t_bsp_node *parent, t_split_infos si, bool left_subvoxel);
double              get_voxel_intersection_cost(t_bsp_node *voxel);


#endif