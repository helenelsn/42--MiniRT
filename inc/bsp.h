/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:46:51 by Helene            #+#    #+#             */
/*   Updated: 2023/11/08 20:16:47 by hlesny           ###   ########.fr       */
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
    int                 depth; // ?
    
    t_bbox_description  bbox;
    t_dim               split_dim; // ?
    
    t_vlist             *items; /* NULL when not a leaf */
    int                 items_count; /* 0 when not a leaf */
    
    struct s_bsp_node   *parent;
    struct s_bsp_node   *left;
    struct s_bsp_node   *right;
}               t_bsp_node;


t_bbox_description  get_scene_limits(t_vlist *objects);

double              compute_cost(t_bsp_node *parent_voxel, t_split_infos si);
double              get_intersection_cost(t_bsp_node *parent, t_split_infos si, bool left_subvoxel);
double              get_object_list_intersection_cost(t_bsp_node *voxel); /* to rename, ca veut r dire la */
t_split_infos       get_optimal_split_plane(t_bsp_node *current_node);
void                split_voxel(t_bsp_node *parent, t_split_infos si);

void                build_kd_tree(t_bsp_node *root_voxel, t_vlist *objects);
void                set_bounding_boxes(t_vlist *objects);
void                bbox_reset(t_bbox_description *bv, t_point_3d p);
void                bbox_add_point(t_bbox_description *bv, t_point_3d p);
void                set_infos(t_bbox_description *bbox);
bool                count_in_cost(t_bbox_description voxel, t_vlist *object);
bool                point_is_in(t_bbox_description bv, t_point_3d p);

t_bbox_description  get_temp_subvoxel(t_bsp_node *parent, t_split_infos si, bool left_subvoxel);
bool                is_in_subvoxel(t_bbox_description subvoxel, t_vlist *object);
bool                intersect_subvoxel(t_bbox_description subvoxel, t_vlist *object);

void                print_kd_tree(t_bsp_node *voxel);


#endif