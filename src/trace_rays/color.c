/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:16:50 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/13 17:14:48 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

int     color_clamp(long color, int min, int max)
{
    if (color < min)
        return (min); // ?
    if (color > max)
        return (max);
    return (color);
}

t_color    color_scale(t_color color, double scale)
{
    if (scale < 0.0)
        return (color); // ?
    // int inter;
    // inter = color.r * scale;
    // if (inter > 255)
    //     inter = 255;
    // color.r = inter;
    // inter = color.g * scale;
    // if (inter > 255)
    //     inter = 255;
    // color.g = inter;
    // inter = color.b * scale;
    // if (inter > 255)
    //     inter = 255;
    // color.b = inter;

    int composant;

    composant = (color.r * scale);// / 255;
    color.r = color_clamp(composant, 0, UCHAR_MAX);

    composant = (color.g * scale);// / 255;
    color.g = color_clamp(composant, 0, UCHAR_MAX);

    composant = (color.b * scale);// / 255;
    color.b = color_clamp(composant, 0, UCHAR_MAX);

    return (color);
}

t_color color_mult(t_color c1, t_color c2)
{
    int color;

    color = (c1.r * c2.r) / 255;
    c1.r = color_clamp(color, 0, UCHAR_MAX);
    
    color = (c1.g * c2.g) / 255;
    c1.g = color_clamp(color, 0, UCHAR_MAX);

    color = (c1.b * c2.b) / 255;
    c1.b = color_clamp(color, 0, UCHAR_MAX);
    return (c1);
}

//todo : proteger en cas d'overflow ?
t_color    color_add(t_color c1, t_color c2)
{
    c1.r = color_clamp(c1.r + c2.r, 0, UCHAR_MAX);
    c1.g = color_clamp(c1.g + c2.g, 0, UCHAR_MAX);
    c1.b = color_clamp(c1.b + c2.b, 0, UCHAR_MAX);
    
    // c1.r += c2.r;
    // c1.g += c2.g;
    // c1.b += c2.b;
    return (c1);
}
