/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_maps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:09:21 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/10 23:04:13 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

void    set_map_dimensions(t_checkers_map *map)
{
    map->height = CHECKERS_HEIGHT;
    map->width = CHECKERS_WIDTH;
}

t_checkers_map  checkers_map_users_input(t_color a, t_color b)
{
    t_checkers_map  map;

    set_map_dimensions(&map);
    map.a = a;
    map.b = b;
    return (map);
}

t_checkers_map  checkers_map_complementary_colors(t_color obj_color)
{
    t_checkers_map map;
    
    set_map_dimensions(&map);
    
    map.a = obj_color;
    map.b.r = UCHAR_MAX - obj_color.r;
    map.b.g = UCHAR_MAX - obj_color.g;
    map.b.b = UCHAR_MAX - obj_color.b;
    return (map);
}

t_checkers_map  checkers_map_white(t_color obj_color)
{
    t_checkers_map map;
    
    set_map_dimensions(&map);
    
    map.a = obj_color;
    map.b = (t_color){0xffffff};
    return map;
}
