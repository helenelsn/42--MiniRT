/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:16:50 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/04 22:37:29 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

int     color_clamp(long color)
{
    if (color < 0)
        return (0); // ?
    if (color > UCHAR_MAX)
        return (UCHAR_MAX);
    return (color);
}

t_color    color_scale(t_color color, double scale)
{

    t_color todel = color;

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

    if (color.hex == 32512)
        printf("--------------- {%s}, initial color = %u, scale = %f\n", __func__, todel.hex, scale);
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