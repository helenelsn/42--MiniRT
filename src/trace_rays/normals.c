/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlesny <hlesny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:06 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/14 00:54:00 by hlesny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ---------------------- NORMALS COMPUTATIONS ----------------------- */

/* need center coordinates */
//tocheck
t_vec	normal_to_sphere(void *obj, t_point p)
{
	t_sphere 	*sp;
	t_vec	normal;

	sp = obj;
	normal = get_directional_vect(sp->p, p);
	
	return (normal);
}

/* produit vectoriel de deux vecteurs generateurs du plan */
//tocheck
t_vec	normal_to_plan(void *obj, t_point p)
{
	t_plan 		*pl;
	
	pl = obj;
	return (pl->vec);
}

/* traduit en coord cylindriques, calcule la normale, puis reconvertit en 
coord cartesiennes (?) */
//todo
t_vec 	normal_to_cylinder(void *obj, t_point p)
{
	t_cylindre	*cy;
	t_vec	normal;
	t_vec		projected;
	t_vec		center_to_hitpoint;

	cy = (t_cylindre *)(obj);
	center_to_hitpoint =  get_directional_vect(cy->p, p);
	// normalise(&center_to_hitpoint);
	projected = vect_double_multiply(dot(center_to_hitpoint, cy->vec), cy->vec);
	
	normal = get_directional_vect(get_vec_coord(projected), get_vec_coord(center_to_hitpoint));
	normalise(&normal);
	return (normal);
}


/*  --------------------------------------------- */

// static t_vector3f	calculate_cone_normal(const t_ray *ray,
// 										const t_object *cone,
// 										const t_hit hit_distance)
// {
// 	if (hit_distance.context == OUTLINE)
// 		return (calculate_outline_cone_normal(ray, cone,
// 				hit_distance.distance));
// 	return (cone->cache.cone.cap_normal);
// }

// t_vector3f	calculate_outline_cone_normal(const t_ray *ray,
// 											const t_object *cone,
// 											const float distance)
// {
// 	const t_vector3f	point = ray_at(ray, distance);
// 	const t_vector3f	point_axe = vector3f_subtract(point,
// 			cone->cache.cone.endpoint2);
// 	const t_vector3f	point_to_axe = vector3f_subtract(cone->position, point);
// 	const t_vector3f	perpendicular_vector = vector3f_cross(\
// 							vector3f_cross(point_axe, point_to_axe), point_axe);

// 	return (vector3f_unit(perpendicular_vector));
// }

// obj_p = center for cylinder
t_vec	normal_to_cap(t_vec dir_obj, t_point obj_p, t_point hit_p)
{
	double projection = dot(get_directional_vect(obj_p, hit_p), dir_obj);
	int sign = (projection > 0.0) - (projection < 0.0);
	
	return (vect_double_multiply(sign, dir_obj));	
}

//todo
t_vec	normal_to_cone(void *obj, t_point p, bool is_cap)
{
	t_cone *cn;
	t_vec	normal;
	t_vec	position;
	double 	ortho_proj;

	cn = obj;
	if (is_cap)
		return (normal_to_cap(cn->vec, cn->p, p));
	
	position = get_directional_vect(cn->top, p);
	
	// normalise(&cn->vec);
	
	ortho_proj = dot(position, cn->vec);
	t_point	proj_p = translate_point(cn->top, vect_double_multiply(ortho_proj, cn->vec));
	t_vec perp_axis = get_directional_vect(proj_p, p);

	t_vec tangent = cross_product(perp_axis, position); // ou - position ?
	normal = cross_product(tangent, perp_axis);

	if (dot(normal, position) < 0.0)
		 normal = vect_double_multiply(-1, normal);

	return (normal);
}

/* computes the normal of a point p on a given object */
t_vec get_unit_normal(t_hit_info hi, t_point p)
{
	t_vec normal;

	if (hi.obj_type == sphere)
		normal = normal_to_sphere(hi.obj_content, p);
	else if (hi.obj_type == plan)
		normal = normal_to_plan(hi.obj_content, p);
	else if (hi.obj_type == cylindre)
		normal = normal_to_cylinder(hi.obj_content, p); // 
	else
		normal = normal_to_cone(hi.obj_content, p, hi.cap_hit);
	
	normalise(&normal);
	return (normal);
}
