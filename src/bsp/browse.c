/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:25 by Helene            #+#    #+#             */
/*   Updated: 2023/11/14 21:09:39 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"
#include "../../inc/bsp.h"


/* t_bsp_node    *position_object_in_tree(t_bsp_node *root, t_vlist *object)
{
    
} */


t_bsp_node	*place_ray_origin_in_tree(t_app app, t_ray ray)
{
	t_bsp_node *curr;

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
