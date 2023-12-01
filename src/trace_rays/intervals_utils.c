/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:09:10 by hlesny            #+#    #+#             */
/*   Updated: 2023/11/30 20:14:44 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

// not sure this one's useful for us
bool surrounds(double x, double min, double max)
{
    return (min < x && x < max);
}

double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return (x);
}

t_interval  get_interval(double min, double max)
{
    t_interval t;

    t.min = min;
    t.max = max;
    return (t);
}