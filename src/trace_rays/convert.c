/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:02:48 by Helene            #+#    #+#             */
/*   Updated: 2023/11/10 01:04:35 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"




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