/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:25 by Helene            #+#    #+#             */
/*   Updated: 2023/11/22 16:53:44 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"


/* t_bsp_node    *position_object_in_tree(t_bsp_node *root, t_vlist *object)
{
    
} */

typedef struct s_stack
{
    t_bsp_node      *node; // pointer to far child
    
    /* double          t_min; // distance d'entrée du rayon dans le noeud
    double          t_max; // distance a laquelle le rayon sort du noeud 
    */
    double          t; /* the entry/exit signed distance */
    t_point_3d      pb; /* the coordinates of entry/exit point */
    int             prev;
    // struct s_stack  *next;
}               t_stack;

bool    intersect_scene(t_bbox_description scene, t_ray ray, float *a, float *b)
{
    (void)scene;
    (void)ray;
    (void)a;
    (void)b;

    return (true); // todel c juste pour que ça compile
}

bool    intersect(t_vlist *obj, t_ray ray, double *dist)
{
    (void)obj;
    (void)ray;
    (void)dist;

    return (true); // todel c juste pour que ça compile
}

/* intersect ray with each object in the object list, discarding
    those lying before stack[enPt].t (ici min) or farther than stack[exPt].t (ici max) */
t_vlist *test_intersections(t_bsp_node *leaf, t_ray ray, double min, double max)
{
    t_vlist *obj;
    t_vlist *closest_obj;
    double  dist;
    double  min_dist;

    obj = leaf->items;
    min_dist = INFINITY;
    dist = INFINITY;
    while (obj)
    {
        if (intersect(obj, ray, &dist) && dist >= min && dist <= max 
            && dist < min_dist)
            {
                min_dist = dist;
                closest_obj = obj;
            }
        obj = obj->next;
    }
    if (min_dist < INFINITY)
        return (closest_obj);
    return (NULL);
}

/* root est dans notre cas le node ou se trouve la camera, et pas la racine du kd-tree (si ?) */
t_vlist *ray_traversal_algo(t_bsp_node *root, t_ray ray)
{
    float   a; /* entry signed distance */
    float   b; /* exit signed distance */
    float   t; /* signed distance to the splitting plane */

    bool    intersect = intersect_scene(root->bbox, ray, &a, &b);
   
    if (!intersect) // ray does not intersect sceneBox
        return (NULL);
    
    /* stack required for traversal to store far children */
    t_stack *stack;
    stack = ft_calloc(sizeof(t_stack), MAX_DEPTH);
    if (!stack) // not enough free memory
        return (NULL);
    
    /* pointers to the far child node and current node */
    t_bsp_node *far_child, *curr_node;
    curr_node = root; /* start from the kd-tree root node */

    int entry_pt = 0; /* setup initial entry point... entry_pt corresponds to pointer */
    stack[entry_pt].t = a; /* set the signed distance */

    /* distinguish between internal and external origin */
    if (a >= 0.0) /* a ray with external origin */
        stack[entry_pt].pb = point_addition(ray.origin, point_double_multiply(a, get_vec_coord(ray.direction)));  // ray.origin + ray.dir * a;
    else /* a ray with internal origin */
        stack[entry_pt].pb = ray.origin;

    /* setup initial exit point in the stack */
    int exit_pt = 1; /* pointer to the stack */
    stack[exit_pt].t = b;
    stack[exit_pt].pb = point_addition(ray.origin, point_double_multiply(b, get_vec_coord(ray.direction))); // ray.origin + ray.dir * b;
    stack[exit_pt].node = NULL; // ?  //"nowhere"; /* set termination flag */


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
            int  prev_axis;
            int  next_axis;
            
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
            t = (split_val - pt_get_coord(ray.origin, curr_node->split_inf.dim)) / vect_get_coord(ray.direction, curr_node->split_inf.dim);
            
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

            double tmp_next = pt_get_coord(ray.origin, next_axis) + t * vect_get_coord(ray.direction, next_axis);
            double tmp_prev = pt_get_coord(ray.origin, prev_axis) + t * vect_get_coord(ray.direction, prev_axis);
            pt_modify_coord(stack[exit_pt].pb, curr_node->split_inf.dim, split_val);
            pt_modify_coord(stack[exit_pt].pb, next_axis, tmp_next);
            pt_modify_coord(stack[exit_pt].pb, prev_axis, tmp_prev);
        }

        /* current node is the leaf . . . empty or full */
        t_vlist *closest_inter = test_intersections(curr_node, ray, stack[entry_pt].t, stack[exit_pt].t);
        /*if ( any intersection exists )
            return ["object with closest intersection point"];*/
        if (closest_inter)
            return (free(stack), closest_inter);

        /* pop from the stack */
        entry_pt = exit_pt; /* the signed distance intervals are adjacent */
        
        /* retrieve the pointer to the next node, it is possible that ray traversal terminates */
        curr_node = stack[exit_pt].node;
        
        exit_pt = stack[entry_pt].prev;
    }
    /* currNode = ”nowhere”, ray leaves the scene */
    return (free(stack), NULL);
}



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
