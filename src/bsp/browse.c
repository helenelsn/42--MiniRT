/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:25 by Helene            #+#    #+#             */
/*   Updated: 2023/11/29 19:48:10 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

typedef struct s_stack
{
    t_bsp_node      *node; // pointer to far child
    
    /* double          t_min; // distance d'entrée du rayon dans le noeud
    double          t_max; // distance a laquelle le rayon sort du noeud 
    */
    double          t; /* the entry/exit signed distance */
    t_point_3d      pb; /* the coordinates of entry/exit point */
    int             prev;
}               t_stack;


//tocheck
bool    intersect_scene(t_bbox_description scene, t_ray ray, float *a, float *b)
{
    float tmin = 0.0;
    float tmax = INFINITY;
    float t1;
    float t2;

    for (int d = 0; d < 3; ++d)
    {
        t1 = (pt_get_coord(scene.min, d) - pt_get_coord(ray.origin, d))
            * (1.0 / vect_get_coord(ray.direction, d));
        t2 = (pt_get_coord(scene.max, d) - pt_get_coord(ray.origin, d))
            * (1.0 / vect_get_coord(ray.direction, d));

        tmin = ft_min(ft_max(t1, tmin), ft_max(t2, tmin));
        tmax = ft_max(ft_min(t1, tmax), ft_min(t2, tmax));
    }

    //tocheck
    *a = tmin;
    *b = tmax;
    
    //if (tmin <= tmax)
    //    printf("------------- {%s}, ray{O(%f, %f, %f), D(%f, %f, %f)} intersects scene\n",
    //    __func__, ray.origin.x, ray.origin,y, ray.origin.z, ray.direction.x, ray.direction.y, ray.direction.z);

    return (tmin <= tmax);
}

/* --------------- intersections ----------------- */

double  get_closest_point(double a, double b) 
{
    if (a <= 0.0 && b <= 0.0)
        return (0.0);
    if (a <= 0.0)
        return (b);
    if (b <= 0.0)
        return (a);
    if (a < b)
        return (a);
    return (b);
}

bool    solve_quadratic_eq(t_quadratic *eq)
{
    double delta;
    double denom; // denominateur

    delta = eq->b * eq->b - 4 * eq->a * eq->c;
    if (delta < 0.0)
        return (false);
    denom = (2 * eq->a); // que faire si 2 * a = 0 ?
    if (delta == 0.0)
    {
        eq->t_1 = - (eq->b / denom);
        eq->t_2 = eq->t_1;
    }
    else
    {
        eq->t_1 = (- eq->b + sqrt(delta)) / denom;
        eq->t_2 = (- eq->b - sqrt(delta)) / denom;
    }
    return (true);
}


bool    intersect_sphere(t_ray *ray, void *object)
{
    t_sphere    *sp;
    t_quadratic eq;
    t_vec_3d    center_to_origin;
    double      mult;

    sp = object;
    center_to_origin = get_directional_vect(sp->p, ray->origin);
    eq.a = vec_x_vec_scal(ray->direction, ray->direction);
    eq.b = 2 * vec_x_vec_scal(center_to_origin, ray->direction);
    eq.c = vec_x_vec_scal(center_to_origin, center_to_origin) - sp->radius * sp->radius;
    if (!solve_quadratic_eq(&eq))
        return (false);
    mult = get_closest_point(eq.t_1, eq.t_2);
    ray->hit_info.hit_point.x = ray->origin.x + ray->direction.x * mult;
    ray->hit_info.hit_point.y = ray->origin.y + ray->direction.y * mult;
    ray->hit_info.hit_point.z = ray->origin.z + ray->direction.z * mult;
    ray->hit_info.coef = mult;
    ray->hit_info.distance = get_dist_between_points(ray->origin, ray->hit_info.hit_point) * (2 * (mult > 0.0) - 1);
    // ray->hit_info.distance = mult;

    //printf("------------- {%s}, ray{O(%f, %f, %f), D(%f, %f, %f)} intersected sphere{C(%f, %f, %f)}\n",
    //    __func__, ray->origin.x, ray->origin,y, ray->origin.z, ray->direction.x, ray->direction.y, ray->direction.z, sp->p.x, sp->p.y, sp->p.z);
    return (ray->hit_info.coef > 0.0);
}

bool    intersect_plan(t_ray *ray, void *object)
{
    t_plan *p;
    t_droite d;
    t_point_3d    res;
    
    
    p = object;
    d.p = ray->origin;
    d.v = ray->direction;
    ray->hit_info.coef = get_inter_for_plan(p, d, &res);
    if (ray->hit_info.coef <= 0)
        return false;

    ray->hit_info.hit_point = res;
    ray->hit_info.distance = get_dist_between_points(ray->origin, ray->hit_info.hit_point);
    return (ray->hit_info.coef > 0.0);
}
// bool intersect_cylinder(t_ray ray, void *object)
// {
    
// }

// bool    intersect_cone(t_ray ray, void *object)
// {
    
// }

//todo
bool    intersect(t_vlist *obj, t_ray *ray)
{

    // mettre a jour le point d intersection, ie ray.hit_inf.hit_point, ainsi 
    // que la distance origine du rayon-object, ie ray.hit_info.distance
    ray->hit_info.distance = -1;
    if (obj->type == sphere)
        return (intersect_sphere(ray, obj->content));
    if (obj->type == plan)
        return (intersect_plan(ray, obj->content));
    // if (obj->type == cylindre)
    //     return (intersect_cylinder(ray, obj->content));
    // if (obj->type == cone)
    //     return (intersect_cone(ray, obj->content));
    
}



void    copy_obj_properties(t_vlist *obj, t_hit_info *hinf, t_point_3d hp)
{
    hinf->obj_content = obj->content;  // est-ce que couille si supprime l objet originel ?
    hinf->obj_type = obj->type;
    hinf->obj_mat = obj->material;
    hinf->hit_point = hp;
}

/* intersect ray with each object in the object list, discarding
    those lying before stack[enPt].t (ici min) or farther than stack[exPt].t (ici max) */
    
//tocheck
void    test_intersections(t_bsp_node *leaf, t_ray *ray, double min, double max)
{
    t_vlist     *obj;
    t_hit_info  *closest_obj;
    double  min_dist;

    closest_obj = ft_calloc(sizeof(t_hit_info), 1);
    if (!closest_obj)
        return ;
    obj = leaf->items;
    min_dist = INFINITY;
    while (obj)
    {
        if (intersect(obj, ray) && ray->hit_info.distance >= min && ray->hit_info.distance <= max 
            && ray->hit_info.distance < min_dist)
            {
                min_dist = ray->hit_info.distance;
                copy_obj_properties(obj, closest_obj, ray->hit_info.hit_point);
            }
        obj = obj->next;
    }
    if (min_dist < INFINITY)
    {
        // a verifier
        ray->hit_info = *closest_obj;
        ray->hit_info.distance = min_dist;
        return ;
    }
    ray->hit_info.distance = -1;
}










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
void    ray_traversal_algo(t_bsp_node *root, t_ray *ray) // *ray traversal pour avoir les modifs ?
{
    float   a; /* entry signed distance */
    float   b; /* exit signed distance */
    float   t; /* signed distance to the splitting plane */


    /* intersect ray with sceneBox, find the entry and exit signed distance */
    bool    intersect = intersect_scene(root->bbox, *ray, &a, &b); 
   
    if (!intersect) // ray does not intersect sceneBox
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
    curr_node = root; /* start from the kd-tree root node */

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
        test_intersections(curr_node, ray, stack[entry_pt].t, stack[exit_pt].t);
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

//t_vlist ray_trav_alg_rec_a(t_bsp_node *root, t_ray ray)
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
