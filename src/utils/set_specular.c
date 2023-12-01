/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_specular.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:14:45 by srapin            #+#    #+#             */
/*   Updated: 2023/12/01 15:24:25 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

bool set_specular(char *str, double *to_mod)
{
    if (!str)
    {
        *to_mod = 0;
        return true;
    }
    if (!ft_strisfloat(str) && !ft_strisint(str))
        return false;
    *to_mod = atof(str);
    if (*to_mod < 0)
        return false;
    return true;
}