/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eva <eva@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:59:58 by Helene            #+#    #+#             */
/*   Updated: 2023/12/13 00:21:24 by eva              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"
#include "../../../inc/mini_rt.h"

void    set_map_dimensions(t_checkers_map *map, t_type elem)
{
    map->height = CHECKERS_HEIGHT;
    map->width = CHECKERS_HEIGHT;
    if (elem == sphere)
        map->width *= 2;
}

void    set_checkerboard_map(t_checkers_map *map, t_type elem, t_color checker_color)
{
    set_map_dimensions(map, elem);
    map->color = checker_color;
}

t_color     checker_color_at(void *object, t_hit_info hit)
{
    t_point_2d  uv;
    double      scaled_u;
    double      scaled_v;

    if (!hit.obj_mat.textures.checkered)
    {
        return (hit.obj_mat.color);
    }
    uv = object_mapping(object, hit);

    //if (uv.u > 1.0 || uv.u < 0.0 || uv.u < 0.0 || uv.v > 1.0)
    //    printf("oh nonnn\n");
    
    scaled_u = floorf(uv.u * hit.obj_mat.textures.checkerboard.width);
    scaled_v = floorf(uv.v * hit.obj_mat.textures.checkerboard.height);
    
    // if ((floor(scaled_u) + floor(scaled_v)) % 2)
        // return (hit.obj_mat.textures.checkerboard.color);
    if (fmodf(scaled_u + scaled_v, 2))
    {
        return (hit.obj_mat.textures.checkerboard.color);
    }
    return (hit.obj_mat.color);
}