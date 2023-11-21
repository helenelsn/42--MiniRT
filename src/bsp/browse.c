/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:25 by Helene            #+#    #+#             */
/*   Updated: 2023/11/21 18:39:05 by Helene           ###   ########.fr       */
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
    struct s_stack  *prev;
    // struct s_stack  *next;
}               t_stack;

bool    intersect_ray_bbox(t_bbox_description bbox, t_ray ray, float *a, float *b)
{
    
}

t_vlist *ray_traversal_algo(t_bsp_node *root, t_ray ray)
{
    float   a; /* entry signed distance */
    float   b; /* exit signed distance */
    float   t; /* signed distance to the splitting plane */

    bool    intersect = intersect_ray_bbox(root->bbox, ray, &a, &b);
   
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
        stack[entry_pt].pb = point_addition(ray.origin, point_double_multiply(a, ray.direction));  // ray.origin + ray.dir * a;
    else /* a ray with internal origin */
        stack[entry_pt].pb = ray.origin;

    /* setup initial exit point in the stack */
    int exit_pt = 1; /* pointer to the stack */
    stack[exit_pt].t = b;
    stack[exit_pt].pb = point_addition(ray.origin, point_double_multiply(b, ray.direction)); // ray.origin + ray.dir * b;
    stack[exit_pt].node = "nowhere"; /* set termination flag */


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
            
            if (pt_get_coord(stack[entry_pt].pb, axis) <= split_val)
            {
                if (pt_get_coord(stack[exit_pt].pb, axis) < split_val) // et non pas <= ?? sinon le if suivant ne sert à rien
                {
                    /* case N1, N2, N3, P5, Z2, and Z3 */
                    curr_node = curr_node->left;
                    continue;
                }
                if (pt_get_coord(stack[exit_pt].pb, axis) == split_val) 
                {
                    curr_node = curr_node->right;
                    continue; /* case Z1  */
                }
                /* case N4 */
                far_child = curr_node->right;
                curr_node = curr_node->left;
            }
            else /* * (stack[enPt].pb[axis] > splitVal) */
            {
                if (split_val < pt_get_coord(stack[exit_pt].pb, axis))
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
            t = (split_val - pt_get_coord(ray.origin, axis)) / vect_get_coord(ray.direction, axis);
            
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

            
            stack[exit_pt].pb[axis] = splitVal;
            stack[exit_pt].pb[nextAxis] = ray.origin[nextAxis] +
            t * ray.dir[nextAxis];
            stack[exit_pt].pb[prevAxis] = ray.origin[prevAxis] +
            t * ray.dir[prevAxis];
        }

        /* current node is the leaf . . . empty or full */
        /* intersect ray with each object in the object list, discarding
        those lying before stack[enPt].t or farther than stack[exPt].t */
        
        /*if ( any intersection exists )
            return ["object with closest intersection point"];*/

        
        
    }
    
}








bool    intersect_ray_plane(t_point_3d min, t_point_3d max, t_dim dim, double coord)
{
    
}

/* returns true if the ray traverses the volume
from left to right, and false otherwise */
bool    orient_ray_plan(t_bbox_description voxel, t_ray ray)
{
    /*
    teste si le rayon traverse le sous voxel gauche ou le sous
    voxel droit en premier
    */
}


t_bsp_node	*place_ray_origin_in_tree(t_app app, t_ray ray)
{
	t_bsp_node *curr;

    curr = &app.root;
    
    if (intersect_ray_bbox(app.root.bbox, ray))
        ;// set t_min and t_max
    else
        return (NULL);
    
    // Pile.push(racine, tmin, tmax)
    while (curr->type == node)
    {
        /* trouver l'orientation du rayon par rapport au plan */
        
        
    }

	return (curr);
}


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
