/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:16:50 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/04 20:16:07 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

char     clamp_color(unsigned int color, double scale)
{
    if (scale < 0.0)
        return (color); // ?
    if (color * scale > UCHAR_MAX)
        return (color);
    return (color * scale);
}

t_color    color_scale(t_color color, double scale)
{
    if (scale < 0.0)
        return (color); // ?
    int inter;
    inter = color.r * scale;
    if (inter > 255)
        inter = 255;
    color.r = inter;
    inter = color.g * scale;
    if (inter > 255)
        inter = 255;
    color.g = inter;

    inter = color.b * scale;
    if (inter > 255)
        inter = 255;
    color.b = inter;
    
    // color.b = inter;
    // int inter;
    // inter = color.r *= scal
    // color.r *= scale;
    // color.g *= scale;
    // color.b *= scale;
    return (color);
}

t_color color_mult(t_color c1, t_color c2)
{
    c1.r = color_clamp(c1.r * c2.r);
    c1.g = color_clamp(c1.g * c2.g);
    c1.b = color_clamp(c1.b * c2.b);
    return (c1);
}

//todo : proteger en cas d'overflow ?
t_color    color_add(t_color c1, t_color c2)
{
    c1.r = color_clamp(c1.r + c2.r);
    c1.g = color_clamp(c1.g + c2.g);
    c1.b = color_clamp(c1.b + c2.b);
    
    // c1.r += c2.r;
    // c1.g += c2.g;
    // c1.b += c2.b;
    return (c1);
}