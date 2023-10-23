/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:02:48 by Helene            #+#    #+#             */
/*   Updated: 2023/10/23 15:35:48 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"

/* Add a function to normalise a vector ? */

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

/* Computes the height and width of the viewpoint, as well as the
distance Camera-Viewpoint according to the field of view (FOV) parameter*/
double    *get_viewpoint_dimensions(float fov)
{
    double viewpoint[2];

    /* Calcule uniquement le width a partir du fov car il s'agit du fov horizontal */
    viewpoint[0] = FOCUS_DIST * tan(fov * 0.5f * DEG_TO_RAD) * 2; /* Width */
    viewpoint[1] = viewpoint[0] * SCREEN_RATIO; /* Height */
    return (viewpoint);
}
