/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:06 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/17 22:51:23 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt_bonus.h"
#include "../../inc/struct_bonus.h"

t_vec	normal_to_sphere(void *obj, t_point p)
{
	t_sphere	*sp;
	t_vec		normal;

	sp = obj;
	normal = get_directional_vect(sp->p, p);
	return (normal);
}

t_vec	normal_to_plan(void *obj)
{
	t_plan	*pl;

	pl = obj;
	return (pl->vec);
}

t_vec	normal_to_cylinder(void *obj, t_hit_info info)
{
	t_cylindre	*cy;
	t_vec		normal;
	t_vec		projected;
	t_vec		center_to_hitpoint;

	cy = (t_cylindre *)(obj);
	if (info.cap_hit)
	{
		if (get_dist_between_points(info.hit_point,
				cy->cover_planes[0].p) < get_dist_between_points(info.hit_point,
				cy->cover_planes[1].p))
			return (cy->vec);
		else
			return (vect_double_multiply(-1, cy->vec));
	}
	center_to_hitpoint = get_directional_vect(cy->p, info.hit_point);
	projected = vect_double_multiply(dot(center_to_hitpoint, cy->vec), cy->vec);
	normal = get_directional_vect(get_vec_coord(projected),
			get_vec_coord(center_to_hitpoint));
	normalise(&normal);
	return (normal);
}

t_vec	normal_to_cone(void *obj, t_point p, bool is_cap)
{
	t_cone	*cn;
	t_vec	point_axe;
	t_ray	tmp;
	t_vec	point_to_axe;
	t_vec	perpendicular_vector;

	cn = obj;
	if (is_cap)
		return (vect_double_multiply(-1, cn->cover_plane.vec));
	point_axe = get_directional_vect(cn->top, p);
	tmp.origin = cn->p;
	tmp.direction = cn->vec;
	point_to_axe = get_directional_vect(cn->p, get_ray_point(tmp, 0));
	perpendicular_vector = cross_product(cross_product(point_axe, point_to_axe),
			point_axe);
	normalise(&perpendicular_vector);
	return (perpendicular_vector);
}

/* computes the normal of a point p on a given object */
t_vec	get_unit_normal(t_hit_info hi, t_point p)
{
	t_vec	normal;

	if (hi.obj_type == plan)
		normal = normal_to_plan(hi.obj_content);
	else if (hi.obj_type == cylindre)
		normal = normal_to_cylinder(hi.obj_content, hi);
	else if (hi.obj_type == sphere)
		normal = normal_to_sphere(hi.obj_content, p);
	else
		normal = normal_to_cone(hi.obj_content, p, hi.cap_hit);
	normalise(&normal);
	return (normal);
}
