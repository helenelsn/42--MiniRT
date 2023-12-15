/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:15:06 by hlesny            #+#    #+#             */
/*   Updated: 2023/12/15 15:31:49 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/struct.h"
#include "../../inc/mini_rt.h"

/* ---------------------- NORMALS COMPUTATIONS ----------------------- */

t_vec	normal_to_sphere(void *obj, t_point p)
{
	t_sphere 	*sp;
	t_vec	normal;

	sp = obj;
	normal = get_directional_vect(sp->p, p);
	
	return (normal);
}

t_vec	normal_to_plan(void *obj, t_point p)
{
	t_plan 		*pl;
	
	pl = obj;
	return (pl->vec);
}

t_vec	project(t_vec projected, t_vec ref)
{
	return (vect_double_multiply(dot(projected, ref), ref));
}

t_vec 	normal_to_cylinder(void *obj, t_hit_info info)
{
	t_cylindre	*cy;
	t_vec	normal;
	t_vec		projected;
	t_vec		center_to_hitpoint;

	cy = (t_cylindre *)(obj);
	if (info.cap_hit)
	{
		if (get_dist_between_points(info.hit_point, cy->cover_planes[0].p) < get_dist_between_points(info.hit_point, cy->cover_planes[1].p))
			return cy->vec;
		else
			return vect_double_multiply(-1, cy->vec);
			// return cy->cover_planes[1].vec;
		// 	return normal_to_cap(cy->cover_planes[1].vec, cy->cover_planes[1].p, info.hit_point);
		// return normal_to_cap(cy->cover_planes[0].vec, cy->cover_planes[0].p, info.hit_point);
		// normal_to_cap
	}
	center_to_hitpoint =  get_directional_vect(cy->p, info.hit_point);
	projected = project(center_to_hitpoint, cy->vec);
	normal = get_directional_vect(get_vec_coord(projected), get_vec_coord(center_to_hitpoint));
	normalise(&normal);
	return (normal);
}

/*  --------------------------------------------- */

// obj_p = center for cylinder
t_vec	normal_to_cap(t_vec dir_obj, t_point obj_p, t_point hit_p)
{
	// double projection = dot(get_directional_vect(hit_p, obj_p), dir_obj);
	// int sign = (projection > 0.0) - (projection < 0.0);
	// return (vect_double_multiply(sign, dir_obj));	
	
	return vect_double_multiply(-1, dir_obj); // ?????????????
}

//todo
t_vec	normal_to_cone2(void *obj, t_point p, bool is_cap)
{
	t_cone *cn;
	t_vec	normal;
	t_vec	position;
	double 	ortho_proj;

	cn = obj;
	if (is_cap)
		return vect_double_multiply(-1, cn->cover_plane.vec);
		// return (normal_to_cap(cn->vec, cn->p, p));
	
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


t_vec	normal_to_cone(void *obj, t_point p, bool is_cap)
{
	t_cone *cn;
	cn = obj;

	if (is_cap)
		return (vect_double_multiply(-1, cn->cover_plane.vec));
	// if (is_cap)
		// return (normal_to_cap(cn->vec, cn->p, p));
	
// const t_vector3f	point = ray_at(ray, distance);
	t_vec point_axe = get_directional_vect(cn->top, p);
	//centre du cylindre 
	t_ray tmp;
	tmp.origin = cn->p;
	tmp.direction = cn->vec;
	t_point position = get_ray_point(tmp, 0);// cn->height/2);
	t_vec point_to_axe = get_directional_vect(cn->p, position );
	
	t_vec	perpendicular_vector = cross_product(cross_product(point_axe, point_to_axe), point_axe);
	normalise(&perpendicular_vector);
	return (perpendicular_vector);
	// return vect_double_multiply(-1, perpendicular_vector);

	// return (vector3f_unit(perpendicular_vector));
}


/* computes the normal of a point P on a given object */
t_vec get_unit_normal(t_hit_info hi, t_point p)
{
	t_vec normal;

	if (hi.obj_type == plan)
		normal = normal_to_plan(hi.obj_content, p);
	else if (hi.obj_type == cone)
		normal = normal_to_cone(hi.obj_content, p, hi.cap_hit);
	else if (hi.obj_type == cylindre)
		normal = normal_to_cylinder(hi.obj_content, hi); // 
	else if (hi.obj_type == sphere)
		normal = normal_to_sphere(hi.obj_content, p);
	else
		printf("type = %d\n", hi.obj_type);
	normalise(&normal);
	return (normal);
}
