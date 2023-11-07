/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bsp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:16 by Helene            #+#    #+#             */
/*   Updated: 2023/11/06 18:35:02 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

/* SAH : Predicts the cost of a defined split position on a per-node basis.
->      A heuristic approach for bintree construction can
        be derived from the observation that the number
        of rays likely to intersect a convex object is roughly
        proportional to its surface area (assuming that the
        ray origins and directions are uniformly distributed
        throughout object space and that all origins are
        sufficiently far from the object).

The bounding volumes associated with nodes are usually referred to as voxels,
which is the threedimensional analog of a pixel. 
*/

t_bsp_node  *new_node(t_vlist *objects)
{
    t_bsp_node *node;

    node = malloc(sizeof(t_bsp_node));
    if (!node)
        return (NULL);

    /* build the node */
    (void)objects;
    return (node);
}

t_bsp_node *new_leaf(t_vlist *objects)
{
    t_bsp_node *leaf;

    leaf = malloc(sizeof(t_bsp_node));
    if (!leaf)
        return (NULL);

    /* build the leaf */
    (void)objects;
    return (leaf);
}

/*
Instead of only using the cost-based termination criterion,
some implementations additionally use the maximum depth criterion, 
usually to reduce memory usage.
*/
bool terminate(t_bsp_node *current, double cost)
{
    /* Teste :
        1) si Nb_triangles * intersect_cost < cost(best_split_plane), 
        ie si c'est rentable de subdiviser a nouveau le voxel 
        2) si on est arrivé à depth_max (reduce memory usage)
        */
    if ((current->items_count * get_voxel_intersection_cost(current) < cost)
        || current->depth == MAX_DEPTH)
        return (true);
    return (false);
}

void rec_build(t_bsp_node *voxel)
{
    t_split_infos si;

    /* get the dimension and coordinates of the split computed with the lowest cost */
    si = get_splitting_plane(voxel);
    
    /* check for terminating-criterias*/
    if (terminate(voxel, si.cost))
    {
        voxel->type = leaf;
        return ;
        // return (new_leaf());
    }
    
    /* create the two subvoxels, and insert the parent's objects in the subvoxels */
    split_voxel(voxel, si);

    /* ?????????? */
    rec_build(voxel->left);
    rec_build(voxel->right);
    
    // return (voxel);
}

void    set_root_voxel(t_bsp_node *root, t_vlist *objects)
{
    t_vlist **curr;

    *curr = objects;
    while (*curr)
    {
        root->items_count++;
        *curr = (*curr)->next;
    }
    root->type = node;
    root->depth = 0;
    root->items = objects;
    root->left = NULL;
    root->right = NULL;
    
    /* set la liste d'objets */
    // root->items = malloc(sizeof(t_vlist), root->items_count);
    
}

/*  Returns the root node 
    Maps the entire scene.
    The camera will then be moved from one node to another 
    depending on its position.
*/
t_bsp_node    *build_kd_tree(t_vlist *objects)
{ 
    t_bsp_node      *root_voxel;

    root_voxel = malloc(sizeof(t_bsp_node));
    if (!root_voxel)
        return (NULL);
    
    /* set each object's bounding box */
    set_bounding_boxes(objects);
    
    /* set the root voxel's dimensions */
    root_voxel->bbox = get_scene_limits(objects);
    
    /* set the root voxel's objects (items) list */
    set_root_voxel(root_voxel, objects);
    
    rec_build(root_voxel); /* ??????? */
    return (root_voxel);
}
