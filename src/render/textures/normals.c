/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:00:07 by Helene            #+#    #+#             */
/*   Updated: 2023/12/16 16:21:12 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"
#include "../../../inc/mini_rt.h"

int	ft_clamp(const int nb, const int min, const int max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

t_vec	get_normal_in_map(t_point_2d uv, t_surface surf)
{
	int			x;
	int			y;
	t_vec	normal;
	t_normal_map *normap;

	normap = get_map_from_type(surf.t);
	if (!normap)
		return (t_vec) {0,0,0,0};
	x = (int) roundf(uv.u * (float)(  normap->width - 1));
	y = (int) roundf(uv.v * (float)(  normap->height - 1));
	x = ft_clamp(x, 0,   normap->width - 1);
	y = ft_clamp(y, 0,   normap->height - 1);
	normal =   normap->pixels[y *   normap->width + x];
	normal = vect_substract(vect_double_multiply(2, normal), (t_vec) {1, 1, 1});
	return normal;
	// normal = vector3f_subtract(vector3f_multiply(normal, 2),
			// vector3f_create(1, 1, 1));
}

static t_vec	get_tangente_space_normal( t_vec world_normal,
											 t_vec map_normal)
{
	t_matrix *mat;
	
	t_vec	tangent;
	t_vec	bitangent;
	t_vec res;

	tangent = cross_product(world_normal, (t_vec) {0, 1, 0, 1});
	
	if (get_v_norm(tangent) == 0)
		tangent = cross_product(world_normal, (t_vec) {0, 0, 1, 1});
	normalise(&tangent);
	bitangent = cross_product(world_normal, tangent);
	normalise(&bitangent);
	mat = new_3x3_matrix_from_vec(tangent, bitangent, world_normal, false); //todo test autre sens
	res = change_base_of_vec(map_normal, (t_vec) {0,0,0,0}, mat);
	normalise(&res);
	return res;
}

t_vec   get_normal_perturbation(t_hit_info hit, void *object)
{
    t_point_2d uv = object_mapping(object, hit);
	t_vec dernorm = get_normal_in_map(uv, hit.obj_mat.textures);
	if (!get_v_norm(dernorm))
		return hit.outward_normal;
	return get_tangente_space_normal(hit.outward_normal, dernorm);
}
