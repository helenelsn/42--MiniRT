/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:29:52 by Helene            #+#    #+#             */
/*   Updated: 2023/12/11 23:03:58 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

// retourner un pointeur plutot ?
t_checkers_map uv_checkers(double width, double height, t_color a, t_color b)
{
    t_checkers_map f;

    f.width = width;
    f.height = height;
    f.a = a;
    f.b = b;

    return (f);
}

t_color uv_pattern_at(t_checkers_map pattern, double u, double v)
{
    int coord;
    
    if (u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0)
    {
        // printf("ohno\n");
        // return (t_color ){255,255,255};
    }
    
    
    coord = (floor(u * pattern.width) + floor(v * pattern.height));
    if (coord % 2)
        return (pattern.a);
    return (pattern.b);
}

typedef struct  s_texture_map
{
    t_point_2d      (*uv_map)(t_point p, t_vlist *obj); // like spherical_map()
    void (*uv_pattern)(t_point_2d uv); // like uv_checkers()
}               t_texture_map;


/* Note : 
If you want your checkers to look "square" on the sphere, be sure and set the width to twice the height. 
This is because of how the spherical map is implemented.
While both u and v go from 0 to 1, v maps 1 to π, but u maps 1 to 2π. */

// t_color pattern_at(t_texture_map map, t_point p, t_vlist *obj) dans le cas de plueurs patterns differents (checks, stripes, ...)
// t_color pattern_at(t_checkers_map map, t_point p, t_type obj_type, void *content)
// {
//     t_point_2d  uv;

//     uv = map_object(p, obj_type, content);
//     return (uv_pattern_at(map, uv.u, uv.v));
// }


t_color checkers_color(t_hit_info hit)
{
    t_point_2d uv;
    t_checkers_map  map;

    map = checkers_map_white(hit.obj_mat.color);

    uv = map_object(hit);
    return (uv_pattern_at(map, uv.u, uv.v));
}
