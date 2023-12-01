/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:16:50 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/01 19:22:57 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

unsigned char   color_clamp(unsigned int c)
{
    if (c > UCHAR_MAX)
        return (UCHAR_MAX);
    return ((unsigned char)c);
}

t_color    color_scale(t_color color, double scale)
{
    if (scale < 0.0)
        return (color); // ?
    
    color.r = color_clamp(color.r * scale);
    color.g = color_clamp(color.g * scale);
    color.b = color_clamp(color.b * scale);
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