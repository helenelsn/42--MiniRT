/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bsp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:16 by Helene            #+#    #+#             */
/*   Updated: 2023/11/03 15:35:33 by Helene           ###   ########.fr       */
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


/*
Instead of only using the cost-based termination criterion,
some implementations additionally use the maximum depth criterion, 
usually to reduce memory usage.
*/
bool    terminate()
{
    
}

void    cost_bias()
{
   /*
    si ( |T_left| = 0 ou |T_left| = 0 )
        bias = 80%
    sinon (Tl et Tr ne sont pas vides)
        bias = 1
   */
}






t_bsp_node  *new_node()
{
    
}

/* returns the root node */
void    *rec_build(t_vlist *objects)
{
    if (terminate())
        return (new_leaf());
    
}

/*  Returns the root node 
    Maps the entire scene.
    The camera will then be moved from one node to another 
    depending on its position.
*/
t_bsp_node    *build_kd_tree(t_vlist *objects)
{
    set_bounding_boxes(objects);
    rec_build(); /* quels arguments ? */
}

