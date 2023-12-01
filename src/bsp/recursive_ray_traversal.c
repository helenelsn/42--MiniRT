/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_ray_traversal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:05:43 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/01 00:38:03 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

typedef struct  s_stack
{
    t_bsp_node  *node;
    float       entry; /* entry signed distance (a) for the node */
    float       exit; /* exit signed distance (b) for the node */
}               t_stack;

t_stack stack_new_elem(t_bsp_node *node, double entry, double exit)
{
    t_stack st; // malloc ?

    st.entry = entry;
    st.exit = exit;
    st.node = node;
    retrun (st);    
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
void    set_near_far_nodes(t_ray *ray, t_bsp_node *curr, t_bsp_node *near, t_bsp_node *far)
{
        
}

bool    tree_ray_traverse(t_app *app, t_bsp_node *node, t_ray *ray, t_interval t)
{
    t_stack     curr;
    double      entry;
    double      exit;
    int         stack_top;

    entry = 0.0;
    exit = 0.0;
    
    if (!intersect_scene(app->root.bbox, *ray, &entry, &exit))
    {
        ray->hit_info.distance = -1;
        return ;
    }

    t_stack *stack;
    stack = ft_calloc(sizeof(t_stack), MAX_DEPTH);
    if (!stack) // not enough free memory
        return ;
    
    stack_top = -1;
    stack_push(stack, &stack_top, stack_new_elem(&app->root, entry, exit));
    

    t_dim   a;
    double  dist;
    t_bsp_node  *curr_node;
    
    while (stack_top >= 0)
    {
        curr = stack[stack_top];
        curr_node = curr.node;
        double  exit_t;
        double  entry_t;

        while (curr_node == node)
        {
            a = curr_node->split_inf.dim;
            dist = (curr_node->split_inf.split_coord - pt_get_coord(ray->origin, a)) / vect_get_coord(ray->direction, a); 

            t_bsp_node *near;
            t_bsp_node *far;
            set_near_far_nodes(ray, curr_node, near, far);
            
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
        if (curr_node->items_count)
        {
            test_inte
        }
    }
    
}