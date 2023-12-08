/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:25 by Helene            #+#    #+#             */
/*   Updated: 2023/12/06 16:46:25 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

#include <math.h>
#include <stdio.h>
typedef struct s_stack
{
    t_bsp_node      *node; // pointer to far child
    
    /* double          t_min; // distance d'entrée du rayon dans le noeud
    double          t_max; // distance a laquelle le rayon sort du noeud 
    */
    double          t; /* the entry/exit signed distance */
    t_point      pb; /* the coordinates of entry/exit point */
    int             prev;
}               t_stack;







/*  ----------------------------------- TA_B_rec ray traversing algorithm ----------------------------------- */

/* pour un rayon r, traverse l'arbre afin de determiner l'intersection du rayon avec les objets
    de la scene.
    si le rayon en intersecte au moins un, on garde le plus proche en memoire.
    on met ainsi la structure t_ray du rayon a jour :
        la distance a l'objet intersecte : ray.hit_info.distance
        le point (x, y, z) de la plus proche intersection du rayon avec l'objet
        les specificites de l'object intersecte : ray.hit_info.obj_type - obj_content - obj_mat
    
    */

/* root est dans notre cas le node ou se trouve la camera, et pas la racine du kd-tree (si ?) */
void    ray_traversal_algo(t_app *app, t_ray *ray) // *ray traversal pour avoir les modifs ?
{
    float   a; /* entry signed distance */
    float   b; /* exit signed distance */
    float   t; /* signed distance to the splitting plane */


    /* intersect ray with sceneBox, find the entry and exit signed distance */
    if (!intersect_scene(app->root.bbox, *ray, &a, &b))
    {
        ray->hit_info.distance = -1;
        return ;
    }
    
    /* stack required for traversal to store far children */
    t_stack *stack;
    stack = ft_calloc(sizeof(t_stack), MAX_DEPTH);
    if (!stack) // not enough free memory
        return ;
    
    /* pointers to the far child node and current node */
    t_bsp_node *far_child, *curr_node;
    curr_node = &app->root; /* start from the kd-tree root node */

    int entry_pt = 0; /* setup initial entry point... entry_pt corresponds to pointer */
    stack[entry_pt].t = a; /* set the signed distance */

    /* distinguish between internal and external origin */
    if (a >= 0.0) /* a ray with external origin */
        stack[entry_pt].pb = point_addition(ray->origin, point_double_multiply(a, get_vec_coord(ray->direction)));  // ray->origin + ray->dir * a;
    else /* a ray with internal origin */
        stack[entry_pt].pb = ray->origin;

    /* setup initial exit point in the stack */
    int exit_pt = 1; /* pointer to the stack */
    stack[exit_pt].t = b;
    stack[exit_pt].pb = point_addition(ray->origin, point_double_multiply(b, get_vec_coord(ray->direction))); // ray->origin + ray->dir * b;
    stack[exit_pt].node = NULL; // ?  //"nowhere"; /* set termination flag */

    int prev_axis;
    int next_axis;

    /* loop, traverse through the whole kd-tree, until an object is intersected or ray leaves the scene */
    while (curr_node)
    {
        /* loop until a leaf is found */
        while (curr_node->type == node)
        {
            /* retrieve position of splitting plane */
            float split_val = curr_node->split_inf.split_coord;

            // ????????????????
            /* similar code for all axes */
            /* nextAxis is x -> y, y -> z, z -> x */
            /* prevAxis is z -> x, y -> x, y -> z */
            if (curr_node->parent)
                prev_axis = curr_node->parent->split_inf.dim;
            else
                prev_axis = x; // ? 
            if (curr_node->right || curr_node->left)
            {
                if (curr_node->right)
                    next_axis = curr_node->right->split_inf.dim;
                else
                    next_axis = curr_node->left->split_inf.dim;
            }
            else
                next_axis = x; // ?

            
            
            if (pt_get_coord(stack[entry_pt].pb, curr_node->split_inf.dim) <= split_val)
            {
                if (pt_get_coord(stack[exit_pt].pb, curr_node->split_inf.dim) < split_val) // et non pas <= ?? sinon le if suivant ne sert à rien
                {
                    /* case N1, N2, N3, P5, Z2, and Z3 */
                    curr_node = curr_node->left;
                    continue;
                }
                if (pt_get_coord(stack[exit_pt].pb, curr_node->split_inf.dim) == split_val) 
                {
                    curr_node = curr_node->right;
                    continue; /* case Z1  */
                }
                /* case N4 */
                far_child = curr_node->right;
                curr_node = curr_node->left;
            }
            else /* * (stack[enPt].pb[curr_node->split_inf.dim] > splitVal) */
            {
                if (split_val < pt_get_coord(stack[exit_pt].pb, curr_node->split_inf.dim))
                {
                    /* case P1, P2, P3, and N5 */
                    curr_node = curr_node->right;
                    continue;
                }
                /* case P4*/
                far_child = curr_node->left;
                curr_node = curr_node->right;
            }
            /* case P4 or N4 . . . traverse both children */
            
            /* signed distance to the splitting plane */
            t = (split_val - pt_get_coord(ray->origin, curr_node->split_inf.dim)) / vect_get_coord(ray->direction, curr_node->split_inf.dim);
            
            /* setup the new exit point */
            int tmp = exit_pt;
            exit_pt++; //Increment(exit_pt);

            /* possibly skip current entry point so not to overwrite the data */
            if (exit_pt == entry_pt)
            exit_pt++; // Increment(exPt);

            /* push values onto the stack */
            stack[exit_pt].prev = tmp;
            stack[exit_pt].t = t;
            stack[exit_pt].node = far_child;

            double tmp_next = pt_get_coord(ray->origin, next_axis) + t * vect_get_coord(ray->direction, next_axis);
            double tmp_prev = pt_get_coord(ray->origin, prev_axis) + t * vect_get_coord(ray->direction, prev_axis);
            pt_modify_coord(stack[exit_pt].pb, curr_node->split_inf.dim, split_val);
            pt_modify_coord(stack[exit_pt].pb, next_axis, tmp_next);
            pt_modify_coord(stack[exit_pt].pb, prev_axis, tmp_prev);
        }

        /* current node is the leaf . . . empty or full */
        test_intersections(curr_node, app->p_data, ray, get_interval(stack[entry_pt].t, stack[exit_pt].t));
        if (ray->hit_info.distance != -1)
        {
            free(stack);
            return ;
        }

        /* pop from the stack */
        entry_pt = exit_pt; /* the signed distance intervals are adjacent */
        
        /* retrieve the pointer to the next node, it is possible that ray traversal terminates */
        curr_node = stack[exit_pt].node;
        
        exit_pt = stack[entry_pt].prev;
    }
    /* currNode = ”nowhere”, ray leaves the scene */
    free(stack);
    //return (free(stack), NULL);
}






/* ---------------------------- TA_A_rec ray traversing algorithm ----------------------------- */

typedef struct  s_stack_elem_a
{
    t_bsp_node  *node;
    float       a; /* entry signed distance (a) for the node */
    float       b; /* exit signed distance (b) for the node */
}               t_stack_elem_a;


/*  Recursive ray traversal algorithm */

//t_vlist ray_trav_alg_rec_a(t_bsp_node *app->root, t_ray ray)
//{
//    float   a; /* entry signed distance */
//    float   b; /* exit signed distance */
//    float   t; /* signed distance to the splitting plane */
//
//    bool    intersect = intersect_scene(root->bbox, ray, &a, &b);
//   
//    if (!intersect) // ray does not intersect sceneBox
//        return (NULL);
//    
//    /* stack required for traversal to store far children */
//    t_stack *stack;
//    stack = ft_calloc(sizeof(t_stack), MAX_DEPTH);
//    if (!stack) // not enough free memory
//        return (NULL);
//    
//    int stack_ptr = 0; /* pointer to the stack */
//    /* pointers to the children node and current node */
//    /* pointers to the far child node and current node */
//    t_bsp_node *far_child, *curr_node;
//    curr_node = root;
//
//    // ------------- todo---------------
//    /* push the initial values onto the stack 
//        -> "store rootNode, a, b onto the stack and increment stackPtr" */
//    
//    while (stack_ptr > 0)
//    {
//        // ---------todo----------------
//        /* pop values from the stack 
//            -> "decrement stackPtr and retrieve currNode, a, and b from the stack" */
//
//        while (curr_node->type == node) // while not a leaf
//        {
//            /* for X axis, Y axis, Z axis compute difference between position of splitting plane and ray origin */
//            // -> le faire pour les 3 axes ? fait aucun sens
//            float diff = pt_get_coord(curr_node->right.bbox.min, curr_node->split_inf.dim) 
//                - pt_get_coord(ray.origin, curr_node->split_inf.dim);
//            /* the signed distance to splitting plane */
//            t = diff / vect_get_coord(ray.direction, curr_node.split_inf.dim);
//
//            * NEGATIVE or POSITIVE cases? */
//            /* the case ZERO is not recognized! */
//            if (diff > 0.0) /* NEGATIVE */
//            {
//                near_child = curr_node->left;
//                far_child = curr_node->right;
//            }
//            else /* POSITIVE */
//            {   
//                near_child = curr_node->right;
//                far_child = curr_node->left;
//            }
//            
//        }
//    }
//}
















/* ok ou a réecrire ? */
t_bsp_node    *position_camera_in_tree(t_bsp_node *root, t_camera cam)
{
    t_bsp_node *curr;

    curr = root;
    
    while (curr && point_is_in(curr->bbox, cam.p) && curr->right)
        curr = curr->right; // ?
    if (curr && point_is_in(curr->bbox, cam.p) && curr->type == leaf)
        return (curr);
    else if (curr && !curr->right && curr->left)
    {
        return (position_camera_in_tree(curr->left, cam));
    } 
    else if (curr && !point_is_in(curr->bbox, cam.p) && curr->parent) 
    {
        return (position_camera_in_tree(curr->parent->left, cam));
    }
    else
        return (NULL); // a modif, mieux ecrire les if car ne devrait pas avoir cette ligne      
}
