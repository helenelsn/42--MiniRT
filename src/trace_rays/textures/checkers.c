/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:59:58 by Helene            #+#    #+#             */
/*   Updated: 2023/12/12 20:50:03 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"
#include "../../../inc/mini_rt.h"

t_color     checker_color_at(void *object, t_hit_info hit)
{
    t_point_2d  uv;
    double      scaled_u;
    double      scaled_v;

    if (!hit.obj_mat.textures.checkered)
        return (hit.obj_mat.color);
    uv = object_mapping(object, hit);
    
    scaled_u = floorf(uv.u * hit.obj_mat.textures.checkerboard.width);
    scaled_v = floorf(uv.v * hit.obj_mat.textures.checkerboard.height);
    
    // if ((floor(scaled_u) + floor(scaled_v)) % 2)
        // return (hit.obj_mat.textures.checkerboard.color);
    if (a_mod_b(scaled_u + scaled_v, 2))
        return (hit.obj_mat.textures.checkerboard.color);
    return (hit.obj_mat.color);
}