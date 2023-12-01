/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_specular.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:14:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/01 17:14:56 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool set_specular(char *str, double *to_mod)
{
    if (!str)
    {
        *to_mod = -1; //*to_mod = 0;
        return true;
    }
    if (!ft_strisfloat(str) && !ft_strisint(str))
        return false;
    *to_mod = atof(str);
    if (*to_mod < 0)
        return false;
    return true;
}