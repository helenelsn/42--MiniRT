/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_reflective.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:20:01 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/08 21:21:30 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool set_reflective(char *str, double *to_mod)
{
    if (!str)
    {
        *to_mod = -1; //*to_mod = 0;
        return true;
    }
    if (!ft_strisfloat(str) && !ft_strisint(str))
        return false;
    *to_mod = atof(str);
    if (*to_mod < 0.0 || *to_mod > 1.0)
        return false;
    return true;
}
