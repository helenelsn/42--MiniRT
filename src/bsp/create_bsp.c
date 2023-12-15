/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bsp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:16 by Helene            #+#    #+#             */
/*   Updated: 2023/12/15 22:38:25 by hlesny           ###   ########.fr       */
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
    
    //printf("get_object_list_intersection_cost : %lf\n", get_object_list_intersection_cost(current));
    

    // cut.cost = (*data).count * INTERSECTION_COST;

    if (get_object_list_intersection_cost(current) < cost)
        return (true);
    return (false);
}

//tocheck
void rec_build(t_bsp_node *voxel)
{
    t_split_infos si;
    
    if (!voxel)
        return ;   

    if (voxel->depth == MAX_DEPTH) // pas sure du premier...  voxel->items_count < 2 || 
    {
        voxel->type = leaf;
        voxel->left = NULL;
        voxel->right = NULL;
        return ;
    }
    /* get the dimension and coordinates of the split computed with the lowest cost */
    si = get_optimal_split_plane(voxel);
    
    /* check for terminating-criterias*/
    if (terminate(voxel, si.cost))
    {
        voxel->type = leaf;
        voxel->split_dim = no_axis;
        voxel->left = NULL;
        voxel->right = NULL;
        return ;
    }
    
    /* create the two subvoxels, and insert the parent's objects in the subvoxels */
    split_voxel(voxel, si);

    /* if (voxel->left)
        rec_build(voxel->left);
    if (voxel->right)
        rec_build(voxel->right); */
    rec_build(voxel->left);
    rec_build(voxel->right);
    
}

void    set_root_voxel(t_bsp_node *root, t_vlist *objects)
{
    t_vlist *curr;

    root->items = malloc(sizeof(t_vlist));
    if (!root->items)
        return ;
    
    curr = objects;
    root->items = objects; /* set la liste d'objets */
    // !!!!!! plutot tout malloc nn ? et ensuite passe les pointeurs aux leafs, pas la peine de re-malloc, aura
    // malloc qu'une liste d'objets pour l'arbre 
    while (curr)
    {
        root->items_count++;
        curr = curr->next;
    }

    
    root->type = node;
    root->depth = 0;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
        
}

/*  Returns the root node.
    Maps the entire scene.
    The camera will then be moved from one node to another 
    depending on its position.
*/
void build_kd_tree(t_bsp_node *root_voxel, t_vlist *objects)
{
    if (!objects)
    {
        root_voxel->type = leaf;
        return ;
    }
    /* set each object's bounding box */
    set_bounding_boxes(objects);
    
    /* set the root voxel's objects (items) list */
    set_root_voxel(root_voxel, objects);
    
    /* set the root voxel's dimensions */
    root_voxel->bbox = get_scene_limits(objects);
    
    /* build the tree */
    rec_build(root_voxel);
}


/* --------------------- printing functions -------------------------- */


void    print_point(t_point p)
{
    printf("(%lf, %lf, %lf)\n", p.x, p.y, p.z);
}

void    print_bbox_infos(t_bbox_description b)
{
    printf("\t\tmin : ");
    print_point(b.min);
    printf("\t\tmax : ");
    print_point(b.max);
    printf("\t\theight : %lf\n", b.height);
    printf("\t\twidth : %lf\n", b.width);
    printf("\t\tlength : %lf\n", b.length);
    printf("\t\tsa : %lf\n", b.surface_area);
}

void    print_dim(t_split_infos si)
{
    printf("\tsplitting dimension : ");
    if (si.dim == x)
        printf("x\n");
    else if (si.dim == y)
        printf("y\n");
    else if (si.dim == z)
        printf("z\n");
    printf("\tsplitting coordinate : %lf\n", si.split_coord);
}

void    print_type(t_vlist *object)
{
    printf("\t\tobject type : ");
    if (object->type == cylindre)
        printf("cylindre\n");
    else if (object->type == cone)
        printf("cone\n");
    else if (object->type == sphere)
        printf("sphere\n");
}

void    print_leaf_infos(t_bsp_node *leaf)
{
    printf("\n------------------Leaf\n");
    printf("\tLeaf depth : %i\n", leaf->depth);
    printf("\t----Voxel's bounding box caracteristics : \n");
    print_bbox_infos(leaf->bbox);
    printf("\t----objects in leaf : \n");
    for (t_vlist *current = leaf->items; current; current = current->next)
    {
        print_type(current);
        printf("\t\t--Object's bounding box caracteristics : \n");
        print_bbox_infos(current->material.bbox);
        printf("\n");
    }
}

void    print_interior_node(t_bsp_node *node)
{
    int i = 0;
    while(i < node->depth)
    {
        printf("    ");
        i++;
    }
    printf("------------------Interior node\n");
    printf("\tNode depth : %i\n", node->depth);
    print_dim(node->split_inf);
    printf("\t----Voxel's bounding box caracteristics : \n");
    print_bbox_infos(node->bbox);
}

void    print_kd_tree(t_bsp_node *voxel)
{
    if (!voxel)
        return ;
    if (voxel->type == leaf)
    {
        int i = 0;
        while(i < voxel->depth)
        {
            printf("    ");
            i++;
        }
        print_leaf_infos(voxel);
        return ;
    }
    else
    {
        print_interior_node(voxel);
        print_kd_tree(voxel->left);
        print_kd_tree(voxel->right);
    }
}
