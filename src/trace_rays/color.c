/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:16:50 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/15 15:22:14 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

unsigned char   rgb_float_to_char(float color)
{
    return ((char)(color * 255.f));
}   

float  rgb_char_to_float(int color_comp)
{
    return (color_comp / 255.f);
}


int     color_clamp(long color, int min, int max)
{
    if (color < min)
        return (min);
    if (color > max)
        return (max);
    return (color);
}

t_color    color_scale(t_color color, double scale)
{
    if (scale < 0.0)
        return (color); // ? // return ((t_color){0, 0, 0})
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

    // int composant;

    // composant = (color.r * scale);// / 255;
    // color.r = color_clamp(composant, 0, UCHAR_MAX);

    // composant = (color.g * scale);// / 255;
    // color.g = color_clamp(composant, 0, UCHAR_MAX);

    // composant = (color.b * scale);// / 255;
    // color.b = color_clamp(composant, 0, UCHAR_MAX);

    return (color);
}

t_color color_mult(t_color c1, t_color c2)
{
    int color;

    color = (float)(c1.r * c2.r) / 255.f;
    c1.r = color_clamp(color, 0, UCHAR_MAX);
    
    color = (float)(c1.g * c2.g) / 255.f;
    c1.g = color_clamp(color, 0, UCHAR_MAX);

    color = (float)(c1.b * c2.b) / 255.f;
    c1.b = color_clamp(color, 0, UCHAR_MAX);
    return (c1);
}

t_color    color_add(t_color c1, t_color c2)
{
    c1.r = color_clamp(c1.r + c2.r, 0, UCHAR_MAX);
    c1.g = color_clamp(c1.g + c2.g, 0, UCHAR_MAX);
    c1.b = color_clamp(c1.b + c2.b, 0, UCHAR_MAX);
    
    return (c1);
}
