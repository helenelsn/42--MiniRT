/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:34:44 by srapin            #+#    #+#             */
/*   Updated: 2023/12/15 19:45:53 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_vec *get_elem_vec(t_hit_info hit)
{
    if (hit.obj_type == plan)
        return &((t_plan *) hit.obj_content)->vec;
    if (hit.obj_type == cylindre)
        return &((t_cylindre *) hit.obj_content)->vec;
    if (hit.obj_type == cone)
        return &((t_cone *) hit.obj_content)->vec;
    return NULL;
}