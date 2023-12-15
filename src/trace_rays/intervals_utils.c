/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:09:10 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/15 15:22:54 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

// not sure this one's useful for us
bool surrounds(double x, double min, double max)
{
    return (min < x && x < max);
}

t_interval  get_interval(double min, double max)
{
    t_interval t;

    t.min = min;
    t.max = max;
    return (t);
}