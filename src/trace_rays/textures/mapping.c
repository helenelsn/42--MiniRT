/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Helene <Helene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:59:51 by Helene            #+#    #+#             */
/*   Updated: 2023/12/15 15:29:14 by Helene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/struct.h"
#include "../../../inc/mini_rt.h"

/* Renvoie l'équivalent (2D) d'un point P (3D),
avec P positionné sur la surface d'un objet (sphère, plan, cylindre, cone)
Ceci, appelé "mapping" diffère selon la géométrie de l'objet 
-> calculates the UV coordinates for a hit position (P) on an object */

t_point_2d   spherical_mapping(t_sphere *sp, t_point p)
{
    // const t_vector3f	position = vector3f_subtract(hit_position,
			// sphere->position);
	// const float			theta = atan2f(position.x, position.z);
	// const float			phi = acosf(position.y / sphere->radius);
	// const float			raw_u = (float)(theta / (2.f * M_PI));
	// return (vector2f_create((raw_u + 0.5f), (float)(phi / M_PI)));

    t_point_2d   uv;
    t_vec       position;
    double      theta;
    double      phi;
    double      raw_u;

    position = get_directional_vect(sp->p, p);
    theta = atan2f(position.x, position.z); // atan2f(position.x, position.z);
    phi = acosf(position.y / sp->radius);
    raw_u = theta / (2.f * M_PI);
    
    uv.u = raw_u + 0.5f; // 1 - (raw_u + 0.5)
    uv.v = phi / M_PI; // 1 - ( phi / M_PI)
    return (uv);
}

// utils
bool	ft_is_equalsf(const float a, const float b, const float tolerance)
{
	return ((a + tolerance >= b) && (a - tolerance <= b));
}

t_vec       vec_mat_product(t_vec v, t_matrix *m)
{
    t_vec   result;
    ft_bzero(&result, sizeof(t_vec));
    
    t_matrix *a = new_matrix_from_var_args(3, 1, v.x, v.y, v.z);
    
    if (m->columns != 3)
        return ((t_vec){0, 0, 0, 0});
    
    for (int i = 0; i < 3; i++)
    {
        result.x += m->matrix[0][i] * a->matrix[i][0];
        result.y += m->matrix[1][i] * a->matrix[i][0];
        result.z += m->matrix[2][i] * a->matrix[i][0];
    }

    del_mat(a);
    return (result);
}

t_matrix	*rotation_matrix_from_angle(double angle, t_vec axis)
{
	t_matrix    *rot;
    float       c;
    float       s; 

    rot = new_void_matrix(3, 3);
    c = cosf(angle);
    s = sinf(angle);

    normalise(&axis);
    
    rot->matrix[0][0] = axis.x * axis.x * (float)(1.0 - c) + c;
    rot->matrix[0][1] = axis.x * axis.y * (float)(1.0 - c) - axis.z * s;
    rot->matrix[0][2] = axis.x * axis.z * (float)(1.0 - c) + axis.y * s;

    rot->matrix[1][0] = axis.y * axis.x * (float)(1.0 - c) + axis.z * s;
    rot->matrix[1][1] = axis.y * axis.y * (float)(1.0 - c) + c;
    rot->matrix[1][2] = axis.y * axis.z * (float)(1.0 - c) - axis.x * s;

    rot->matrix[2][0] = axis.x * axis.z * (float)(1.0 - c) - axis.y * s;
    rot->matrix[2][1] = axis.y * axis.z * (float)(1.0 - c) + axis.x * s;
    rot->matrix[2][2] = axis.z * axis.z * (float)(1.0 - c) + c;

    return rot;
}

double  radians_to_degrees(double radians)
{
    return (radians * 180.0 / M_PI);
}


t_vec    rotate_relative_pos(t_vec surface_normal, t_point hit_point, t_point obj_p)
{
    t_vec       position;
    float		rotation_phi;
    t_matrix    *rotation_mat;
    t_vec       rot_axis;

    position = get_directional_vect(obj_p, hit_point);
    
    if (!ft_is_equalsf(surface_normal.y, 1.f, FLT_EPSILON))
	{
        // angle <normal.y, y-axis>
        // rotation_phi = radians_to_degrees(acosf(surface_normal.y));
        
        t_vec unit_vector = {0, 1, 0}; // the (0,1,0) unit vector
        double dot_product = surface_normal.x * unit_vector.x + surface_normal.y * unit_vector.y + surface_normal.z * unit_vector.z;
        double norm_product = get_v_norm(surface_normal) * get_v_norm(unit_vector);
		double cos_theta = dot_product / norm_product;
        double theta = acos(cos_theta);
        
        //rotates the relative position to align with the Y-Axis
        rot_axis = cross_product(unit_vector, surface_normal);
        
        rotation_mat = rotation_matrix_from_angle(-theta, rot_axis);
        
		position = change_base_of_vec(position, (t_vec){0,0,0,0}, rotation_mat);
        // position = vec_mat_product(position, rotation_mat);
        
        del_mat(rotation_mat);
	}
    return (position);
}

float	fmodf_positive(float dividend, float divisor)
{
	float	result;

	result = fmodf(dividend, divisor);
	if (result < 0)
		result = divisor + result;
	return (result);
}

/*
The calculate_planar_map function calculates the UV coordinates for a hit position on a plane.
It first subtracts the position of the plane from the hit position to get a relative position.
If the plane's axis is not aligned with the Y-axis, it rotates the position to align with the Y-axis.
The U and V coordinates are then calculated as the modulus of the X and Z coordinates of the position, respectively
*/
t_point_2d   planar_mapping(t_plan *pl, t_point p)
{
    t_point_2d   uv;
    t_vec       position;

    position = rotate_relative_pos(pl->vec, p, pl->p);
        
	uv.u = fmodf_positive(position.x, 1.0);
	uv.v = fmodf_positive(position.z, 1.0);

	return (uv);
}

t_point_2d  cap_mapping(t_point p, t_vec surface_normal, t_point hit_point, double radius)
{
    t_point_2d  uv;
    t_vec       position;

    position = rotate_relative_pos(surface_normal, hit_point, p);
    uv.u = a_mod_b((position.x + radius) / (radius * 6), 1); // a_mod_b((position.x + radius) / (radius * 2), 1);
	uv.v = a_mod_b((position.z + radius) / (radius * 6), 1);
    return (uv);
}

t_point_2d   cylindrical_mapping(t_cylindre *cy, t_hit_info hit)
{
    t_point_2d  uv;
    t_vec       position;
    double      theta;
    double      raw_u;
      
    if (hit.cap_hit)
        return (cap_mapping(cy->p, cy->vec, hit.hit_point, cy->radius));
    
    position = rotate_relative_pos(cy->vec, hit.hit_point, cy->p);
    theta = atan2f(position.x / cy->radius,
			position.z / cy->radius);
	raw_u = theta / (float)(2.f * M_PI);
    
	uv.u = 1.f - (raw_u + 0.5f);
	uv.v = (0.5f + position.y / cy->height);        
    
    return (uv);
}

t_point_2d  conical_mapping(t_cone *co, t_hit_info hit)
{
    t_point_2d  uv;
    t_vec       position;
    double      theta;
    double      raw_u;
      
    if (hit.cap_hit)
        return (cap_mapping(co->p, co->vec, hit.hit_point, co->radius));
    
    position = rotate_relative_pos(co->vec, hit.hit_point, co->p);
    theta = atan2f(position.x / co->radius,
			position.z / co->radius);
	raw_u = theta / (float)(2.f * M_PI);
    
	uv.u = 1.f - (raw_u + 0.5f);
	uv.v = (0.5f + position.y / co->height);        
    
    return (uv);
}

t_point_2d  object_mapping(void *object, t_hit_info hit)
{
    if (hit.obj_type == sphere)
        return (spherical_mapping((t_sphere *)object, hit.hit_point));
    else if (hit.obj_type == plan)
        return (planar_mapping((t_plan *)object, hit.hit_point));
    else if (hit.obj_type == cylindre)
        return (cylindrical_mapping((t_cylindre *)object, hit));
    else // if (hit.obj_type == cone)
        return (conical_mapping((t_cone *)object, hit));
}
