/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_ray_traversal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:05:43 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/12 16:23:42 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"

typedef struct  s_stack
{
    t_bsp_node  *node;
    float       entry; /* entry signed distance (a) for the node */
    float       exit; /* exit signed distance (b) for the node */
}               t_stack;

//tocheck
bool    intersect_scene(t_bbox_description scene, t_ray ray, double *a, double *b)
{
    double tmin = 0.0;
    double tmax = INFINITY;
    double t1;
    double t2;

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


/* intersect ray with each object in the object list, discarding
    those lying before stack[enPt].t (ici min) or farther than stack[exPt].t (ici max) */
    
//tocheck
bool    test_intersections(t_bsp_node *leaf, t_parsing_data pdata, t_ray *ray, t_interval t)
{
    t_vlist     *obj;
    t_hit_info  *closest_obj;
    double  min_dist;

    closest_obj = ft_calloc(sizeof(t_hit_info), 1);
    if (!closest_obj)
        return (false);
    
    min_dist = t.max;
    
    obj = leaf->items;
    while (obj)
    {
        // set_color_in_mat(obj->content, &obj->material, obj->type);
        if (intersect(obj, ray) && ray->hit_info.distance < min_dist
            && ray->hit_info.distance >= t.min && ray->hit_info.distance <= t.max)
            {
                min_dist = ray->hit_info.distance;
                copy_obj_properties(obj, closest_obj, ray->hit_info.hit_point);
            }
        obj = obj->next;
    }
    
    obj = pdata.planes;
	while (obj)
    {
		// set_color_in_mat(obj->content, &obj->material, obj->type);
		// set_specular_in_mat(obj->content, &obj->material, obj->type);
        if (intersect(obj, ray) && ray->hit_info.distance >= t.min
			&& ray->hit_info.distance < min_dist)
        	{
        	    min_dist = ray->hit_info.distance;
        	    copy_obj_properties(obj, closest_obj, ray->hit_info.hit_point);
				
        	}
        obj = obj->next;
    }
    
    if (min_dist < t.max)
    {
        // a verifier
        ray->hit_info = *closest_obj;
        ray->hit_info.distance = min_dist;
        return (true);
    }
    return (false);
}






t_stack stack_new_elem(t_bsp_node *node, double entry, double exit)
{
    t_stack st; // malloc ?

    st.entry = entry;
    st.exit = exit;
    st.node = node;
    return (st);    
}

t_stack     stack_pop(t_stack *stack, int *stack_top)
{
    // if (*stack_top < 0)
    //     return ;
    return (stack[(*stack_top)--]);
}

void    stack_push(t_stack *stack, int *stack_top, t_stack new_elem)
{
    stack[++(*stack_top)] = new_elem;   
}

// les set ici (passer l'adresse), ou juste dire si s'agit de l'enfant
// droit ou gauche ?
// returns true if near node is the left-child node, false otherwise
void    set_near_far_nodes(double ray_origin_coord, t_bsp_node *curr, t_bsp_node *near, t_bsp_node *far)
{
    if (ray_origin_coord < curr->split_inf.split_coord)
    {
        near = curr->left;
        far = curr->right;   
    }
    else
    {
        near = curr->right;
        far = curr->left;
    }
}

/*  a tester : le cas ou le rayon est identique au plan de coupe -> verifier que crash pas */
void    rec_ray_traverse(t_app *app, t_ray *ray, t_interval t) // t_bsp_node *node, 
{
    t_stack     curr;
    double      entry;
    double      exit;
    int         stack_top;

    entry = 0.0;
    exit = 0.0;
    
    ray->hit_info.distance = -1;
    if (!intersect_scene(app->root.bbox, *ray, &entry, &exit))
        return ;

    t_stack *stack;
    stack = ft_calloc(sizeof(t_stack), MAX_DEPTH);
    if (!stack) // not enough free memory
        return ;
    
    stack_top = -1;
    stack_push(stack, &stack_top, stack_new_elem(&app->root, entry, exit));
    

    t_dim   a;
    double  dist;
    t_bsp_node  *curr_node;
    curr_node = NULL;
        
    while (stack_top >= 0)
    {
        curr = stack_pop(stack, &stack_top); // stack[stack_top];
        curr_node = curr.node;
        double  entry_t = curr.entry;
        double  exit_t = curr.exit;

        // printf("{%s}, stack_top = %d\n", __func__, stack_top);

        while (curr_node && curr_node->type == node)
        {
            a = curr_node->split_inf.dim;
            dist = (curr_node->split_inf.split_coord - pt_get_coord(ray->origin, a)) / vect_get_coord(ray->direction, a); 

            t_bsp_node *near;
            t_bsp_node *far;
            set_near_far_nodes(pt_get_coord(ray->origin, a), curr_node, near, far);
            
            if (dist > exit_t || dist < 0.0)
                curr_node = near;
            else if (dist < entry_t)
                curr_node = far;
            else
            {
                stack_push(stack, &stack_top, stack_new_elem(far, dist, exit_t));
                curr_node = near;
                exit_t = dist;
            }
        }
        // if the current node isn't an empty leaf -> intersect ray with each objects of the leaf
        if (curr_node && curr_node->items_count)
        {
            if (test_intersections(curr_node, app->p_data, ray, t))
            {
                // free stack
                free(stack);
                return;   
            }
        }
    }
    return ;
}