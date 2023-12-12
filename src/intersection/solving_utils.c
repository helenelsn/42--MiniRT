/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:55:39 by Helene            #+#    #+#             */
/*   Updated: 2023/12/12 15:56:08 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

double  get_closest_point(double a, double b) 
{
    if (a <= 0.0 && b <= 0.0)
        return (0.0);
    if (a <= 0.0)
        return (b);
    if (b <= 0.0)
        return (a);
    if (a < b)
        return (a);
    return (b);
}

bool    solve_quadratic_eq(t_quadratic *eq)
{
    double delta;
    double denom; // denominateur

    delta = eq->b * eq->b - 4 * eq->a * eq->c;
    eq->t_1 = 0;
    eq->t_2 = 0;
    if (delta < 0.0)
        return (false);
    denom = (2 * eq->a); // que faire si 2 * a = 0 ?
    if (delta == 0.0)
    {
        eq->t_1 = - (eq->b / denom);
        eq->t_2 = eq->t_1;
    }
    else
    {
        eq->t_1 = (- eq->b + sqrt(delta)) / denom;
        eq->t_2 = (- eq->b - sqrt(delta)) / denom;
    }
    return (true);
}