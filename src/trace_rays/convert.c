/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:02:48 by Helene            #+#    #+#             */
/*   Updated: 2023/11/08 21:08:59 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"


/* Computes the position of the current pixel on the 
camera's projection plane (ie viewpoint) */
t_point_3d canvas_to_viewpoint(t_point_2d c, double v_width, double v_height, double d) // d, Vh et Vw singletons ?
{
    t_point_3d v;

    v.x = v_width * (c.x / SCREEN_WIDTH)    
    v.y = v_height * (c.y / SCREEN_HEIGHT);
    v.z = d;
    return (v);
}


t_point_2d  canvas_to_screen(t_point_2d c)
{
    t_point_2d s;

    s.x = SCREEN_WIDTH / 2 + c.x;
    s.y = SCREEN_HEIGHT / 2 - c.y;
    return (s);
}

/* Computes the height and width of the viewpoint, 
according to the field of view (FOV) parameter*/

//->>>>>>commenter pour compilation (todo add garbage et malloc le tableau ou prendre le tab en argument)

double    *get_viewpoint_dimensions(float fov)
{
    double viewpoint[2];

    viewpoint[0] = FOCUS_DIST * tan(fov * 0.5f * DEG_TO_RAD) * 2; /* Width */
    viewpoint[1] = viewpoint[0] * SCREEN_RATIO; /* Height */
    return (viewpoint);
}