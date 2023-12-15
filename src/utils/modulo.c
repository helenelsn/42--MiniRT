/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:25:26 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/15 21:39:42 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

// int     ft_sign(double n)
// {
//     if (n < 0.0)
//         return (-1);
//     return (1);
// }

double  a_mod_b(double a, int n)
{
    int     k;
    bool    neg;

    if (!n)
        return (0); // idk
    k = 0;
    if (a < 0.0)
        neg = true;
    a = fabs(a);
    // printf("a = %f\n", a);
    while (k * n < a)
        k++;
    if (neg)
        return (k * n - a);
    return (a - (k - 1) * n);   
   
}
