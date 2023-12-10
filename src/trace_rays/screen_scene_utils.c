/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_scene_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:12:10 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/10 18:51:38 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ------------------ SCREEN - SCENE CONVERTIONS UTILS --------------- */



/* Computes the position of the current pixel on the 
camera's projection plane (ie viewpoint) */
/* t_point  pixel_to_viewpoint_coord(int x, int y)
{
    t_point v;

    v.x = viewp_width * (x / IMAGE_WIDTH);
    v.y = viewp_height * (y / IMAGE_HEIGHT);
    v.z = FOCUS_DIST;
    return (v);
} */

/* canvas = centre au milieu (et non pas (0,0) en haut a gauche de l'ecran) */
t_point_2d  pixel_to_screen(t_point_2d c)
{
    t_point_2d s;

    s.u = IMAGE_WIDTH / 2 + c.u;
    s.v = IMAGE_HEIGHT / 2 - c.v;
    return (s);
}