/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:46:51 by Helene            #+#    #+#             */
/*   Updated: 2023/11/03 14:54:11 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSP_H
# define BSP_H

#include <stdbool.h>
#include "struct.h"

/* variables pour les conditions d'arrêt de la fonction récursive créant l'arbre */
# define    MAX_ELEMS /* nombre maximal d'éléments géométriques pouvant etre dans une feuille finale */
# define    MAX_DEPTH /* profondeur maximale de l'arbre */

# define TRAVERSE_COST          1 // a modif /* cost of traversing an inner node */ 
# define UNITARY_INTERSECT_COST 1 // a modif /* cost of intersecting a triangle (ici ne décompose pas en triangles, donc devra ponderer selon la surface de l'objet i guess) */

/* 
In ray tracing the internal nodes of a space subdivision are not interesting.
All useful information is in the leaves.
*/

typedef enum    e_type
{
    node,
    leaf  
}               t_type;

typedef enum    e_dim
{
    x,
    y,
    z
}               t_dim;

typedef struct  s_bbox_voxel_intersect_info
{
    t_dim       splitting_dim; /* sur quelle dimension on split  */
    t_point_3d  intersections[4]; // est a la norme ça ? me souviens jamais
    int         items_count; /* ?? */
}               t_bbox_voxel_intersect_info;

typedef struct s_bsp_node
{
    t_type          type; 
    int             depth; /* ? */
    
    /* when an interior node */
    int             splitting_dim; /*  (i.e. x, y, or z) */
    t_plan          split_plane; /* le representer avec une donnée plus simple ? */
    
    /* when a leaf node */
    t_vlist         *items; /* NULL when not a leaf */
    int             items_count; /* 0 when not a leaf ? */
    
    struct s_bsp_node    *left;
    struct s_bsp_node    *right;
}               t_bsp_node;


#endif