/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:02:48 by Helene            #+#    #+#             */
/*   Updated: 2023/10/23 13:29:43 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"

/* Add a function to normalise a vector ? */

# define CW 1400.0
# define CH 800.0
/*
Vx = width of the viewpoint
Vh = height of the viewpoint
d = distance Camera-Viewpoint */

/* Computes the position of the current pixel on the 
camera's projection plane (ie viewpoint) */
t_point_3d canvas_to_viewpoint(t_point_2d c, double v_width, double v_height, double d) // d, Vh et Vw singletons ?
{
    t_point_3d v;

    v.x = v_width * (c.x / CW);
    v.y = v_height * (c.y / CH);
    v.z = d;
    return (v);
}

t_point_2d  canvas_to_screen(t_point_2d c)
{
    t_point_2d s;

    s.x = CW / 2 + c.x;
    s.y = CH / 2 - c.y;
    return (s);
}


# define FOCUS_DIST 1
# define DEG_TO_RAD 180/M_PI 
# define SCREEN_RATIO  16/9

/* Computes the height and width of the viewpoint, as well as the
distance Camera-Viewpoint according to the field of view (FOV) parameter*/
double    *get_viewpoint_dimensions(float fov)
{
    double viewpoint[2];

    viewpoint[0] = FOCUS_DIST * tan(fov * 0.5f * DEG_TO_RAD) * 2; /* Width */
    viewpoint[1] = viewpoint[0] * SCREEN_RATIO; /* Height */
    return (viewpoint);
}