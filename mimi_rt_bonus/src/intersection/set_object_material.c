/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object_material.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:52:57 by Helene            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"
#include "../../inc/struct_bonus.h"

void	copy_obj_properties(t_vlist *obj, t_hit_info *hit, t_hit_info to_copy)
{
	hit->obj_content = obj->content;
	hit->obj_type = obj->type;
	hit->obj_mat = obj->material;
	hit->hit_point = to_copy.hit_point;
	hit->cap_hit = to_copy.cap_hit;
}
