/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:59:58 by Helene            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/mini_rt_bonus.h"
#include "../../../inc/struct_bonus.h"

void	set_map_dimensions(t_checkers_map *map, t_type elem)
{
	map->height = CHECKERS_HEIGHT;
	map->width = CHECKERS_HEIGHT;
	if (elem == sphere)
		map->width *= 2;
}

void	set_checkerboard_map(t_checkers_map *map, t_type elem,
		t_color checker_color)
{
	set_map_dimensions(map, elem);
	map->color = checker_color;
}

t_color	checker_color_at(void *object, t_hit_info hit)
{
	t_point_2d	uv;
	double		scaled_u;
	double		scaled_v;

	if (!hit.obj_mat.textures.checkered)
		return (hit.obj_mat.color);
	uv = object_mapping(object, hit);
	scaled_u = floorf(uv.u * hit.obj_mat.textures.checkerboard.width);
	scaled_v = floorf(uv.v * hit.obj_mat.textures.checkerboard.height);
	if (fmodf(scaled_u + scaled_v, 2))
		return (hit.obj_mat.textures.checkerboard.color);
	return (hit.obj_mat.color);
}
