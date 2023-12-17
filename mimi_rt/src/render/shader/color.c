/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:16:50 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/16 17:33:35 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/mini_rt.h"
#include "../../../inc/struct.h"

int	color_clamp(long color, int min, int max)
{
	if (color < min)
		return (min);
	if (color > max)
		return (max);
	return (color);
}

t_color	color_scale(t_color color, double scale)
{
	int	inter;

	if (scale < 0.0)
		return (color);
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
	return (color);
}

t_color	color_mult(t_color c1, t_color c2)
{
	int	color;

	color = (float)(c1.r * c2.r) / 255.f;
	c1.r = color_clamp(color, 0, UCHAR_MAX);
	color = (float)(c1.g * c2.g) / 255.f;
	c1.g = color_clamp(color, 0, UCHAR_MAX);
	color = (float)(c1.b * c2.b) / 255.f;
	c1.b = color_clamp(color, 0, UCHAR_MAX);
	return (c1);
}

t_color	color_add(t_color c1, t_color c2)
{
	c1.r = color_clamp(c1.r + c2.r, 0, UCHAR_MAX);
	c1.g = color_clamp(c1.g + c2.g, 0, UCHAR_MAX);
	c1.b = color_clamp(c1.b + c2.b, 0, UCHAR_MAX);
	return (c1);
}
