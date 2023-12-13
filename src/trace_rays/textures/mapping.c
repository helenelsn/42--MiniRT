/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eva <eva@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:59:51 by Helene            #+#    #+#             */
/*   Updated: 2023/12/13 01:24:07 by eva              ###   ########.fr       */
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
    
    // float x = axis.x;
    // float y = axis.y;
    // float z = axis.z;

    rot->matrix[0][0] = axis.x * axis.x * (1-c) + c;
    rot->matrix[0][1] = axis.x * axis.y * (1-c) - axis.z * s;
    rot->matrix[0][2] = axis.x * axis.z * (1-c) + axis.y * s;

    rot->matrix[1][0] = axis.y * axis.x * (1-c) + axis.z * s;
    rot->matrix[1][1] = axis.y * axis.y * (1-c) + c;
    rot->matrix[1][2] = axis.y * axis.z * (1-c) - axis.x * s;

    rot->matrix[2][0] = axis.x * axis.z * (1-c) - axis.y * s;
    rot->matrix[2][1] = axis.y * axis.z * (1-c) + axis.x * s;
    rot->matrix[2][2] = axis.z * axis.z * (1-c) + c;

    return rot;
}

double  rad_to_deg(double radians)
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
		rotation_phi = rad_to_deg(acosf(surface_normal.y));
        
        //rotates the og_p relative position to align with the Y-Axis
        rot_axis = cross_product((t_vec){0, 1, 0}, surface_normal);
        normalise(&rot_axis);
        
        // rot_axis = vector3f_unit(vector3f_cross(vector3f_create(0, 1, 0), plane->axis));
        rotation_mat = rotation_matrix_from_angle(-rotation_phi, rot_axis);
		position = change_base_of_vec(position, (t_vec){0,0,0,0}, rotation_mat);
        // position = vec_mat_product(position, rotation_mat);
        
        // position = quaternionf_rotate_vector3f(-rotation_phi,
				// vector3f_unit(vector3f_cross(vector3f_create(0, 1, 0), \
				// plane->axis)), position);
	}
    del_mat(rotation_mat);
    return (position);
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
    // position = get_directional_vect(pl->p, p);   
	// if (!ft_is_equalsf(pl->vec.y, 1.f, FLT_EPSILON))
	// {
	// 	rotation_phi = rad_to_deg(acosf(pl->vec.y));
        
    //     t_vec rot_axis = cross_product((t_vec){0, 1, 0}, pl->vec);
    //     normalise(&rot_axis);
    //     rotation_mat = rotation_matrix_from_angle(-rotation_phi, rot_axis);
	// 	position = change_base_of_vec(position, (t_vec){0,0,0,0}, rotation_mat);
	// }

    double test = dot(position, pl->vec);
    
	uv.u = a_mod_b(position.x, 1); // modulof_positive()
	uv.v = a_mod_b(position.z, 1);

	return (uv);
}

t_point_2d  cap_mapping(t_point p, t_vec surface_normal, t_point hit_point, double radius)
{
    t_point_2d  uv;
    t_vec       position;

    position = rotate_relative_pos(surface_normal, hit_point, p);
    uv.u = a_mod_b((position.x + radius) / (radius * 2), 1);
	uv.v = a_mod_b((position.z + radius) / (radius * 2), 1);
}

t_point_2d   cylindrical_mapping(t_cylindre *cy, t_hit_info hit)
{
    t_point_2d  uv;
    t_vec       position;
    double      theta;
    double      raw_u;
      
    if (hit.cap_hit)
        return (cap_mapping(cy->p, hit.outward_normal, hit.hit_point, cy->radius));
        
    position = rotate_relative_pos(hit.outward_normal, hit.hit_point, cy->p);
    theta = atan2f(position.x / cy->radius,
			position.z / cy->radius);
	raw_u = theta / (float)(2.f * M_PI);
    
	uv.u = 1.f - (raw_u + 0.5f);
	uv.v = (0.5f + position.y / cy->height);
    
    return (uv);
}

t_point_2d  conical_mapping(t_cone *co, t_hit_info hit)
{
    
}

t_point_2d  object_mapping(void *object, t_hit_info hit)
{
    if (hit.obj_type == sphere)
        return (spherical_mapping((t_sphere *)object, hit.hit_point));
    else if (hit.obj_type == plan)
        return (planar_mapping((t_plan *)object, hit.hit_point));
    else if (hit.obj_type == cylindre)
        return (cylindrical_mapping((t_cylindre *)object, hit));
    else // hit.obj_type == cone
        return (conical_mapping((t_cone *)object, hit));
}