/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_scene_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:12:10 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/28 18:30:59 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------------ SCREEN - SCENE CONVERTIONS UTILS --------------- */

int	viewp_height;
int viewp_width;

//tocheck
//tomodif : creer les singletons a la place des globales
void 	get_viewpoint_dimensions(float fov)
{
    viewp_width = FOCUS_DIST * tan(fov * 0.5f * DEG_TO_RAD) * 2; /* Width */
    viewp_height = viewp_width * ASPECT_RATIO; /* Height */

    // set the viewpoint's height and width singletons 
}

/* Computes the position of the current pixel on the 
camera's projection plane (ie viewpoint) */
t_point_3d  pixel_to_viewpoint_coord(int x, int y)
{
    t_point_3d v;

    v.x = viewp_width * (x / SCREEN_WIDTH);
    v.y = viewp_height * (y / SCREEN_HEIGHT);
    v.z = FOCUS_DIST;
    return (v);
}

/* canvas = centre au milieu (et non pas (0,0) en haut a gauche de l'ecran) */
t_point_2d  pixel_to_screen(t_point_2d c)
{
    t_point_2d s;

    s.x = SCREEN_WIDTH / 2 + c.x;
    s.y = SCREEN_HEIGHT / 2 - c.y;
    return (s);
}